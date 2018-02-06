#include "Maestro.h"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <type_traits>

#include <SFML/Graphics.hpp>

namespace MAESTRO_NAMESPACE
{
	///
	void Maestro::Run()
	{

	}

	///
	template<typename SysType> 
	bool Maestro::AddSystem()
	{
		auto sysType = GetSystemIndex<SysType>();
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			if (it->first == sysType)
			{
				printf("FATAL ERROR: Cannot add system " + sysType.name + "; system already exists.")
				return false;
			}			
		}
		systems.push_back(std::make_pair(sysType, SysType()));
		return true;
	}

	///
	template<typename SysType>
	bool Maestro::RemoveSystem()
	{
		auto sysType = GetSystemIndex<SysType>();
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			if (it->first == sysType)
			{
				systems.erase(it--);
				return true;
			}
		}
		return false;
	}

	///
	template<typename SysType> 
	System *Maestro::GetSystem()
	{
		auto sysType = GetSystemIndex<SysType>();
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			if (it->first == sysType)
			{
				return &(it->second);
			}
		}
		return nullptr;
	}

	///
	template<typename SysType> 
	std::type_index Maestro::GetSystemIndex()
	{
		std::static_assert(std::is_base_of<System, SysType>::value, "SysType does not inherit System.");
		return typeid(SysType);
	}

	void Maestro::OnCreate()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnCreate();
		}
	}

	void Maestro::OnStart()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnStart();
		}
	}

	void Maestro::OnUpdate()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnUpdate();
		}
	}

	void Maestro::OnRender()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnRender();
		}
	}

	void Maestro::OnFinish()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnFinish();
		}
	}

	void Maestro::OnDestroy()
	{
		for (auto it = systems.begin(); it != systems.end(); ++it)
		{
			it->second.OnDestroy();
		}
	}

}