
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
	
	/// <summary>
	/// Runs the Maestro engine 
	/// </summary>
	void Run();

	/// <summary>
	/// Adds a system to the engine's update loop.
	/// </summary>
	/// <returns>True if the System was successfully added, false otherwise.</returns>
	template<typename S> static bool AddSystem();

	/// <summary>
	/// Removes a System from the engine's update loop.
	/// </summary>
	/// <returns>True if the system was successfully removed, false otherwise.</returns>
	template<typename S> static bool RemoveSystem();
	
	/// <summary>
	/// Retrieves a System currently in the engine's update loop.
	/// </summary>
	/// <returns>The System if it exists, or nullptr otherwise.</returns>
	template<typename S> static System *const GetSystem();

	/// <summary>
	/// Retrieves a System currently in the engine's update loop.
	/// </summary>
	/// <param name="s">The system's type_index.</param>
	/// <returns>The System if it exists, or nullptr otherwise.</returns>
	static System *const GetSystemFromTypeIndex(std::type_index s);

	/// <summary>
	///	Assigns the component designated in the template argument to a system to be managed. 
	/// The system managing this component is responsible for the creation and destruction of the component in memory, as well as updating the component.
	/// </summary>
	/// <param name="system">The managing System if there is one, or nullptr otherwise.</param>
	/// <returns></returns>
	template<typename C> static bool SetManagingSystem(System *const system);

	/// <summary>
	/// Retrieves the System in charge of managing the Component.
	/// </summary>
	/// <returns>A const pointer to the managing System if it exists, or nullptr otherwise.</returns>
	template<typename C> static System *const GetManagingSystem();

	/// <summary>
	/// Retrieves a type_index for the given system. This method also checks the validity of the system being indexed.
	/// </summary>
	/// <returns>The System's type_index.</returns>
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

///
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