#include "Engine.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <Windows.h>
#include <direct.h>
#include "Logging.h"

#include <typeinfo>
#include <typeindex>

namespace mae
{

	///
	Engine::Engine()
		: systems()
		, managers()
	{
	}

	///
	void Engine::Run()
	{
		OnCreate();

		currentTime = GetHiresTimeSeconds();

		while (isRunning)
		{
			double newTime = GetHiresTimeSeconds();
			deltaTime = newTime - currentTime;
			elapsedTime += deltaTime;
			currentTime = newTime;
			accumulator += deltaTime;

			if (!isStarted)
			{
				OnStart();
				isStarted = true;
			}

			// dan: make this more robust later

			// regular update
			OnUpdate();

			// fixed update
			if (accumulator > 0.2)
			{
				accumulator = 0.2;
			}

			while (accumulator > DELTATIME_FIXED)
			{
				OnFixedUpdate();
				accumulator -= deltaTime;
			}

			// render
			OnRender();

			if (!isRunning)
			{
				OnFinish();
				break;
			}
		}

		OnDestroy();
	}

	void Engine::OnCreate()
	{
		t0 = std::chrono::high_resolution_clock::now();
		
		if (!CheckStorage(MINIMUM_SPACE_REQUIRED))
		{
			LOG_ERROR("Could not initialize Maestro: Insufficient storage.");
			exit(1);
		}

		if(!CheckMemory(MINIMUM_PHYSICAL_MEMORY_REQUIRED, MINIMUM_VIRTUAL_MEMORY_REQUIRED))
		{
			LOG_ERROR("Could not initialize Maestro: Insufficient memory.");
			exit(1);
		}
		
		ReadCPUSpeed();
		ReadCPUArch();

		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			LOG_ERROR("Could not initialize SDL2: ", SDL_GetError());
			exit(1);
		}

		window = SDL_CreateWindow("Maestro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			LOG_ERROR("Could not create window: ", SDL_GetError());
			exit(1);
		}

		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(window);

		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnCreate();
		}
		LOG_WARNING(__FUNCTION__);

		gameModeStack.top()->OnCreate();

	}

	void Engine::OnStart()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnStart();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnStart();

	}

	void Engine::OnUpdate()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnUpdate();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnUpdate();
	}

	void Engine::OnFixedUpdate()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnFixedUpdate();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnFixedUpdate();
	}

	void Engine::OnRender()
	{
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0X00, 0x00, 0x00));

		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnRender();
		}
		LOG_MESSAGE(__FUNCTION__);
		
		SDL_UpdateWindowSurface(window);
	}

	void Engine::OnFinish()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnFinish();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnFinish();
	}

	void Engine::OnDestroy()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnDestroy();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnDestroy();
		
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool Engine::RemoveSystem(std::type_index sysType)
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			auto st = std::type_index(typeid(*(*it)));
			if (st == sysType)
			{
				(*it)->OnDestroy();
				delete (*it);
				systems.erase(it--);
				return true;
			}
		}
		return false;
	}

	System * const Engine::GetSystem(std::type_index sysType)
	{
		auto it = std::find_if(systems.begin(), systems.end(), [=](System *v)->bool
		{
			return std::type_index(typeid(*v)) == sysType;
		});
		System *const res = (it != std::end(systems)) ? *it : nullptr;

		//printf("Engine::GetSystem(%s) -> %p\n", sysType.name(), res);
		return res;
	}

	System * const Engine::GetManagingSystem(std::type_index cmpType)
	{

		auto type = managers[cmpType];
		if (type == nonstd::nullopt)
		{
			return nullptr;
		}

		//printf("Engine::GetManagingSystem(%s) -> %s\n", cmpType.name(), type->name());
		return GetSystem(*type);
	}

	bool Engine::SetManagingSystem(System * const system, std::type_index cmpType)
	{
		auto type = nonstd::make_optional(std::type_index(typeid(*system)));
		if (type == nonstd::nullopt)
		{
			return false;
		}
		managers[cmpType] = type;
		return true;
	}

	bool Engine::CheckStorage(const unsigned long long diskSpaceNeeded)
	{
		// Check for enough free disk space on the current disk.
		int const drive = _getdrive();
		struct _diskfree_t diskfree;
		_getdiskfree(drive, &diskfree);
		unsigned __int64 const neededClusters = (diskSpaceNeeded * 1048576) /
			(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
		if (diskfree.avail_clusters < neededClusters) {
			// if you get here you dont have enough disk space!
			LOG_ERROR("CheckStorage Failure : Not enough physical storage.");
			isRunning = false;
			return false;
		}
		LOG_MESSAGE("Sufficient disk space. Only %i MB needed.\n", diskSpaceNeeded);
		return true;
	}

	bool Engine::CheckMemory(const unsigned long long physicalRAMNeeded, const	unsigned long long virtualRAMNeeded)
	{
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		if ((status.ullTotalPhys / 1048576) < physicalRAMNeeded) {
			LOG_ERROR("CheckMemory Failure : Not enough physical memory.");
			isRunning = false;
			return false;
		}
		else
		{
			LOG_MESSAGE("Sufficient Physical Memory. Physical Memory Available: %i MB available.\n", (status.ullAvailPhys / 1048576));
		}
		// Check for enough free memory.
		if ((status.ullAvailVirtual / 1048576) < virtualRAMNeeded)
		{
			LOG_ERROR("CheckMemory Failure : Not enough virtual memory.");
			isRunning = false;
			return false;
		}
		else
		{
			LOG_MESSAGE("Sufficient Virtual Memory. Virtual Memory Available: %u MB vailable.\n", (status.ullAvailVirtual / 1048576));
		}
		return true;
	}

	std::string Engine::ReadCPUArch()
	{
		DWORD BufSize = 1024;
		char name[1024];
		std::string dwMHz;
		DWORD type = REG_SZ;
		HKEY hKey;
		// open the key where the proc speed is hidden:
		long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
		if (lError == ERROR_SUCCESS) {
			// query the key:
			RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)&name, &BufSize);
		}
		//std::cout << "Your CPU Architecture: \n" << name << std::endl;
		LOG_MESSAGE("Your CPU Architecture: %s \n", name);
		return std::string(name);
	}

	unsigned long Engine::ReadCPUSpeed()
	{
		DWORD BufSize = sizeof(DWORD);
		DWORD dwMHz = 0;
		DWORD type = REG_DWORD;
		HKEY hKey;
		// open the key where the proc speed is hidden:
		long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
		if (lError == ERROR_SUCCESS) {
			// query the key:
			RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
			LOG_MESSAGE("CPU Speed is ~%f GHz.\n", ((float)dwMHz * 0.001f));
		}
		return dwMHz;
	}

	const double Engine::GetHiresTimeSeconds() const
	{
		using namespace std::chrono;

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		duration<double> time_span = duration_cast<duration<double>>(t1 - t0);
		return time_span.count();
	}
}
