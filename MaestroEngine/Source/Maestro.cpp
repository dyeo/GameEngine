#include "Maestro.h"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <type_traits>

#include <SFML/Graphics.hpp>

///
void Maestro::Run()
{
	OnCreate();

	currentTime = GetHiresTimeSeconds() - DELTATIME_FIXED;

	while (isRunning)
	{
		double newTime = GetHiresTimeSeconds();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		if (!isStarted)
		{
			OnStart();
			isStarted = true;
		}

		while (accumulator >= DELTATIME_FIXED)
		{
			OnUpdate();

			accumulator -= DELTATIME_FIXED;
			elapsedTime += DELTATIME_FIXED;
		}

		OnRender();
	}

	OnFinish();
	OnDestroy();

	getchar();
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