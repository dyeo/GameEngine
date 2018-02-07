#include "Maestro.h"

#include <assert.h>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

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
	// andrew: initialization code goes here

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

const double Maestro::GetHiresTimeSeconds() const
{
	auto t0 = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::seconds>(std::chrono::seconds(0));
	auto t1 = std::chrono::high_resolution_clock::now();
	auto s0 = std::chrono::time_point_cast<std::chrono::seconds>(t0);
	auto s1 = std::chrono::time_point_cast<std::chrono::seconds>(t1);
	return std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0).count();
}