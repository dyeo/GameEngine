
#ifndef _MAESTRO_MAESTRO_H_
#define _MAESTRO_MAESTRO_H_

#include "Updatable.h"
#include "System.h"

#include <vector>
#include <map>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <optional.h>

class Maestro : public Updatable
{
public:

	void Run();

	template<typename S> static bool AddSystem();
	template<typename S> static bool RemoveSystem();

	template<typename S> static System *const GetSystem();
	static System *const GetSystemFromTypeIndex(std::type_index s);

	template<typename C> static bool SetManagingSystem(System *const system);
	template<typename C> static System *const GetManagingSystem();
	template<typename S> static std::type_index GetSystemIndex();

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

	// application state
	bool isStarted = false;
	bool isRunning = true;
	// bool isPaused = false;
	// bool hasFocus = true;

	// timestepping
	const double GetHiresTimeSeconds() const;
	double elapsedTime = 0.0f;
	double currentTime = 0.0f; 
	double deltaTime = 0.0f;

private:

	static std::vector<System> systems;
	static std::map<std::type_index, nonstd::optional<std::type_index>> managers;
};

///
template<typename S>
inline bool Maestro::AddSystem()
{
	auto sysType = GetSystemIndex<S>();
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		auto st = std::type_index(typeid(*it));
		if (st == sysType)
		{
			printf("FATAL ERROR: Cannot add system " + sysType.name + "; system already exists.");
			return false;
		}
	}
	systems.push_back(std::make_pair(sysType, S(this)));
	return true;
}

///
template<typename S>
inline bool Maestro::RemoveSystem()
{
	auto sysType = GetSystemIndex<S>();
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		auto st = std::type_index(typeid(*it));
		if (st == sysType)
		{
			systems.erase(it--);
			return true;
		}
	}
	return false;
}

///
template<typename S>
inline System *const Maestro::GetSystem()
{
	auto sysType = GetSystemIndex<S>();
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

template<typename C>
inline bool Maestro::SetManagingSystem(System * const system)
{
	static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
	auto type = nonstd::make_optional(std::type_index(typeid(system)));
	if (type == nonstd::nullopt)
	{
		return false;
	}
	managers[std::type_index(typeid(C))] = type;
	return true;
}

///
template<typename C>
inline System * const Maestro::GetManagingSystem()
{
	auto type = managers[typeid(C)];
	if (type == nonstd::nullopt)
	{
		return nullptr;
	}
	return GetSystemFromTypeIndex(*type);
}

///
template<typename S>
inline std::type_index Maestro::GetSystemIndex()
{
	static_assert(std::is_base_of<System, S>::value, "S does not inherit System.");
	return std::type_index(typeid(S));
}

#endif // !_MAESTRO_MAESTRO_H_