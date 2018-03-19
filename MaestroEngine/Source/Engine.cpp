#include "Engine.h"

#include <SFML/Graphics.hpp>

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

		while (true)
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

			if (!isRunning || !window.isOpen())
			{
				OnFinish();
				break;
			}
		}

		OnDestroy();

		getchar();
	}

	void Engine::OnCreate()
	{
		t0 = std::chrono::high_resolution_clock::now();

		window.create(sf::VideoMode(1920, 1080), "Maestro Test Window");

		splashTexture = new sf::Texture();
		if (splashTexture->loadFromFile("./Assets/splash.png") != true)
		{
			LOG_ERROR("Splash screen image not found. Not really fatal, but c'mon man you need one.");
			isRunning = false;
			return;
		}
		splashSprite = new sf::Sprite();
		splashSprite->setTexture(*splashTexture);

		CheckStorage(MINIMUM_SPACE_REQUIRED);
		CheckMemory(MINIMUM_PHYSICAL_MEMORY_REQUIRED, MINIMUM_VIRTUAL_MEMORY_REQUIRED);
		ReadCPUSpeed();
		ReadCPUArch();

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

		if (elapsedTime >= 3.0f)
		{
			delete splashSprite;
			splashSprite = nullptr;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
				window.close();
				return;
			}
		}
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

		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			(*it)->OnRender();
		}
		LOG_MESSAGE(__FUNCTION__);

		gameModeStack.top()->OnRender();

		window.clear();
		if (splashSprite != nullptr)
		{
			window.draw(*splashSprite);
		}
		window.display();
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
