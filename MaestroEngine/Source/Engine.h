#ifndef _MAESTRO_ENGINE_H_
#define _MAESTRO_ENGINE_H_

// maestro includes
#include "Updatable.h"
#include "System.h"

// external includes
#include <optional.h>
#include <SFML/Graphics.hpp>

// standard includes
#include <cstdint>
#include <chrono>
#include <vector>
#include <map>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

#define MINIMUM_SPACE_REQUIRED 300
#define MINIMUM_PHYSICAL_MEMORY_REQUIRED 1024
#define MINIMUM_VIRTUAL_MEMORY_REQUIRED 1024

namespace mae
{	
	/// <summary>
	/// The main Engine object. Responsible for interfacing with the operating system, managing systems, providing the update loop, and managing additional update threads.
	/// </summary>
	class Engine : public Updatable
	{
		// methods
	public:
		
		/// <summary>
		/// Default constructor.
		/// </summary>
		Engine();

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
		/// Called once per physics frame for this Updatadable.
		/// </summary>
		virtual void OnFixedUpdate() override;

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
		template<typename S> bool AddSystem();

		/// <summary>
		/// Removes a System from the engine's update loop.
		/// </summary>
		/// <returns>True if the system was successfully removed, false otherwise.</returns>
		template<typename S> bool RemoveSystem();

		/// <summary>
		/// Removes a System from the engine's update loop.
		/// </summary>
		/// <param name="sysType">The System type.</param>
		/// <returns>True if the system was successfully removed, false otherwise.</returns>
		bool RemoveSystem(std::type_index sysType);

		/// <summary>
		/// Retrieves a System currently in the engine's update loop.
		/// </summary>
		/// <returns>The System if it exists, or nullptr otherwise.</returns>
		template<typename S> System *const GetSystem();

		/// <summary>
		/// Retrieves a System currently in the engine's update loop.
		/// </summary>
		/// <param name="sysType">The System type.</param>
		/// <returns>The System if it exists, or nullptr otherwise.</returns>
		System *const GetSystem(std::type_index sysType);

		/// <summary>
		/// Retrieves a System currently in the engine's update loop.
		/// </summary>
		/// <param name="s">The system's type_index.</param>
		/// <returns>The System if it exists, or nullptr otherwise.</returns>
		System *const GetSystemFromTypeIndex(std::type_index s);

		/// <summary>
		///	Assigns the component designated in the template argument to a system to be managed. 
		/// The system managing this component is responsible for the creation and destruction of the component in memory, as well as updating the component.
		/// </summary>
		/// <param name="system">The managing System.</param>
		/// <returns>True if the managing System was successfully set, or false otherwise.</returns>
		template<typename C> bool SetManagingSystem(System *const system);

		/// <summary>
		///	Assigns the component designated in the template argument to a system to be managed. 
		/// The system managing this component is responsible for the creation and destruction of the component in memory, as well as updating the component.
		/// </summary>
		/// <param name="system">The managing System.</param>
		/// <param name="cmpType">The Component type.</param>
		/// <returns>True if the managing System was successfully set, or false otherwise.</returns>
		bool SetManagingSystem(System *const system, std::type_index cmpType);

		/// <summary>
		/// Retrieves the System in charge of managing the Component.
		/// </summary>
		/// <returns>A const pointer to the managing System if it exists, or nullptr otherwise.</returns>
		template<typename C> System *const GetManagingSystem();

		/// <summary>
		/// Retrieves the System in charge of managing the Component.
		/// </summary>
		/// <param name="cmpType>The Component's type.</param>
		/// <returns>A const pointer to the managing System if it exists, or nullptr otherwise.</returns>
		System *const GetManagingSystem(std::type_index cmpType);

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
		
		/// <summary>
		/// Gets the time since the engine was created in seconds, using the highest-resolution clock available to the system.
		/// </summary>
		/// <returns>Returns the elapsed time, in seconds.</returns>
		const double GetHiresTimeSeconds() const;

		// members
	public:

		// application state
		bool isStarted = false;
		bool isRunning = true;
		// bool isPaused = false;
		// bool hasFocus = true;

		// timestepping
		const double DELTATIME_FIXED = 1.0 / 60.0;
		double elapsedTime = 0.0;
		double currentTime = 0.0;
		double deltaTime = 0.0;

	private:

		friend class Component;

		double accumulator = 0.0;
		std::chrono::time_point<std::chrono::high_resolution_clock> t0;

		std::vector<System> systems;
		std::map<std::type_index, nonstd::optional<std::type_index>> managers;
		
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
			std::type_index st(typeid(*it));
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
		return RemoveSystem(sysType);
	}

	///
	template<typename S>
	inline System *const Engine::GetSystem()
	{
		auto sysType = GetSystemIndex<S>();
		return GetSystem(sysType);
	}

	///
	template<typename C>
	inline bool Engine::SetManagingSystem(System *const system)
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		return SetManagingSystem(system, typeid(C));
	}

	///
	template<typename C>
	inline System * const Engine::GetManagingSystem()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		return GetManagingSystem(typeid(C));
	}

	///
	template<typename S>
	inline std::type_index Engine::GetSystemIndex()
	{
		static_assert(std::is_base_of<System, S>::value, "Generic S does not inherit System.");
		return std::type_index(typeid(S));
	}

}

#endif // !_MAESTRO_ENGINE_H_