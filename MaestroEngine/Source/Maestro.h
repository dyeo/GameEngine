
#ifndef _MAESTRO_MAESTRO_H_
#define _MAESTRO_MAESTRO_H_

#include "Updatable.h"
#include "System.h"

#include <vector>
#include <utility>
#include <typeindex>

class Maestro : public Updatable
{
public:

	void Run();

	template<typename S> bool AddSystem();
	template<typename S> bool RemoveSystem();
	template<typename S> System *GetSystem();

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
	const double DELTATIME_FIXED = 1.0 / 60.0;
	double elapsedTime = 0.0f;
	double currentTime = 0.0f;
	double accumulator = 0.0f;

private:

	std::vector<System> systems;

};

///
template<typename S>
inline bool Maestro::AddSystem()
{
	auto sysType = GetSystemIndex<S>();
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		if (typeid(*it) == sysType)
		{
			printf("FATAL ERROR: Cannot add system " + sysType.name + "; system already exists.")
				return false;
		}
	}
	systems.push_back(std::make_pair(sysType, S()));
	return true;
}

///
template<typename S>
inline bool Maestro::RemoveSystem()
{
	auto sysType = GetSystemIndex<S>();
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		if (typeid(*it) == sysType)
		{
			systems.erase(it--);
			return true;
		}
	}
	return false;
}

///
template<typename S>
inline System *Maestro::GetSystem()
{
	auto sysType = GetSystemIndex<S>();
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		if (typeid(*it) == sysType)
		{
			return &(it->second);
		}
	}
	return nullptr;
}

///
template<typename S>
inline std::type_index Maestro::GetSystemIndex()
{
	std::static_assert(std::is_base_of<System, S>::value, "S does not inherit System.");
	return typeid(S);
}

#endif // !_MAESTRO_MAESTRO_H_