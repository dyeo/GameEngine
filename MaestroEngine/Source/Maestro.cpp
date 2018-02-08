#include "Maestro.h"

#include <assert.h>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <direct.h>

std::vector<System> Maestro::systems = std::vector<System>();
std::map<std::type_index, nonstd::optional<std::type_index>> Maestro::managers = std::map<std::type_index, nonstd::optional<std::type_index>>();

///
void Maestro::Run()
{
	OnCreate();

	currentTime = GetHiresTimeSeconds();
	
	while (isRunning)
	{
		double newTime = GetHiresTimeSeconds();
		currentTime = newTime;
		deltaTime = newTime - currentTime;

		if (!isStarted)
		{
			OnStart();
			isStarted = true;
		}

		// dan: make this more robust later

		OnUpdate();
		OnRender();
	}

	OnFinish();
	OnDestroy();

	getchar();
}

///
System * const Maestro::GetSystemFromTypeIndex(std::type_index sysType)
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		auto st = std::type_index(typeid(*it));
		if (st == sysType)
		{
			return it._Ptr;
		}
	}
	return nullptr;
}

void Maestro::OnCreate()
{
	CheckStorage(MINIMUM_SPACE_REQUIRED);
	CheckMemory(MINIMUM_PHYSICAL_MEMORY_REQUIRED, MINIMUM_VIRTUAL_MEMORY_REQUIRED);
	ReadCPUSpeed();
	ReadCPUArch();

	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnCreate();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

void Maestro::OnStart()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnStart();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

void Maestro::OnUpdate()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnUpdate();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

void Maestro::OnRender()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnRender();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

void Maestro::OnFinish()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnFinish();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

void Maestro::OnDestroy()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		it->OnDestroy();
	}
	#ifdef _DEBUG
		printf("%s\n", __FUNCSIG__);
	#endif // _DEBUG
}

bool Maestro::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = (diskSpaceNeeded * 1048576) /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters) {
		// if you get here you dont have enough disk space!
		printf("CheckStorage Failure : Not enough physical storage.");
		isRunning = false;
		return false;
	}
	printf("Sufficient disk space. Only %i MB needed.\n", diskSpaceNeeded);
	return true;
}

bool Maestro::CheckMemory(const DWORDLONG physicalRAMNeeded, const	DWORDLONG virtualRAMNeeded) {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	if ((status.ullTotalPhys / 1048576) < physicalRAMNeeded) {
		printf("CheckMemory Failure : Not enough physical memory.");
		isRunning = false;
		return false;
	}
	else
	{
		printf("Sufficient Physical Memory. Physical Memory Available: %i MB available.\n", (status.ullAvailPhys / 1048576));
	}
	// Check for enough free memory.
	if ((status.ullAvailVirtual / 1048576) < virtualRAMNeeded) {
		printf("CheckMemory Failure : Not enough virtual memory.");
		isRunning = false;
		return false;
	}
	else
	{
		printf("Sufficient Virtual Memory. Virtual Memory Available: %u MB vailable.\n", (status.ullAvailVirtual/ 1048576));
	}
	return true;
}

std::string Maestro::ReadCPUArch() {
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
	std::cout << "Your processor Architecture: \n" << name << std::endl;
	return std::string(name);
}

DWORD Maestro::ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
		printf("CPU Speed is ~%f GHz.\n", ((float)dwMHz * 0.001f));
	}
	return dwMHz;
}

const double Maestro::GetHiresTimeSeconds() const
{
	auto t0 = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::seconds>(std::chrono::seconds(0));
	auto t1 = std::chrono::high_resolution_clock::now();
	auto s0 = std::chrono::time_point_cast<std::chrono::seconds>(t0);
	auto s1 = std::chrono::time_point_cast<std::chrono::seconds>(t1);
	return std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0).count();
}