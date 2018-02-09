#ifndef _MAESTRO_ENGINE_H_
#define _MAESTRO_ENGINE_H_

#include "Updatable.h"
#include "System.h"

#include <vector>
#include <map>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <optional.h>

#include <SFML/Graphics.hpp>

#define MINIMUM_SPACE_REQUIRED 300
#define MINIMUM_PHYSICAL_MEMORY_REQUIRED 1024
#define MINIMUM_VIRTUAL_MEMORY_REQUIRED 1024

namespace mae
{

	class Engine : public Updatable
	{
		// methods
	public:
		
		/// <summary>
		/// Default constructor.
		/// </summary>
		Engine() {};

		/// <summary>
		/// Virtual destructor.
		/// </summary>
		virtual ~Engine() override {};

		/// <summary>
		/// Called once when the Updatable is created, before OnStart or OnUpdate.
		/// </summary>
		virtual void OnCreate() override;

		/// <summary>
		/// Called once during the update loop for this Updatable, before the first OnUpdate.
		/// </summary>
		virtual void OnStart() override;

		/// <summary>
		/// Called during the update loop for this Updatable, and is called at least once per frame.
		/// </summary>
		virtual void OnUpdate() override;

		/// <summary>
		/// Called following OnUpdate for this Updatable, and is called as many times as possible per frame (or once per frame if vsync is enabled).
		/// </summary>
		virtual void OnRender() override;

		/// <summary>
		/// Called once after the update loop for this Updatable, before any Updatables in this object's update loop are destroyed.
		/// </summary>
		virtual void OnFinish() override;

		/// <summary>
		/// Called after OnFinish for this Updatable, before the object is destroyed.
		/// </summary>
		virtual void OnDestroy() override;

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

		/// <summary>
		/// Checks the storage.
		/// </summary>
		/// <param name="diskSpaceNeeded">The disk space needed in MB.</param>
		/// <returns>returns your input value if the requirement is met</returns>
		bool CheckStorage(const unsigned long long diskSpaceNeeded);

		/// <summary>
		/// Checks the memory.
		/// </summary>
		/// <param name="physicalRAMNeeded">The physical ram needed.</param>
		/// <param name="virtualRAMNeeded">The virtual ram needed.</param>
		/// <returns>return two values if the requirements are met; physical memory, and virtual memory.</returns>
		bool CheckMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded);

		/// <summary>
		/// Reads the cpu arch.
		/// </summary>
		/// <returns>The CPU Architecture as defined in the Registry.</returns>
		std::string ReadCPUArch();

		/// <summary>
		/// Reads the system CPU speed.
		/// </summary>
		/// <returns>The system CPU speed, in MHz.</returns>
		unsigned long ReadCPUSpeed();

		// members
	public:

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

		sf::RenderWindow window;
		sf::Sprite *splashSprite;
		sf::Texture *splashTexture;

	};

	///
	template<typename S>
	inline bool Engine::AddSystem()
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
	inline bool Engine::RemoveSystem()
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
	inline System *const Engine::GetSystem()
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
	inline bool Engine::SetManagingSystem(System * const system)
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
	inline System * const Engine::GetManagingSystem()
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
	inline std::type_index Engine::GetSystemIndex()
	{
		static_assert(std::is_base_of<System, S>::value, "S does not inherit System.");
		return std::type_index(typeid(S));
	}

}

#endif // !_MAESTRO_ENGINE_H_