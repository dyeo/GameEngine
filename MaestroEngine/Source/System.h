#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Updatable.h"

#include <cstdint>
#include <typeindex>
#include <vector>

namespace mae
{

	class Engine;
	class Component;
	class Entity;
	
	/// <summary>
	/// A System to be managed by the Engine. Hooks into the Engine's update loop and manages Components that it claims through communication with the Engine. 
	/// Systems are responsible for allocating new Components on request, appropriately calling their OnStart and OnFinish methods, updating them according to their purpose, and destroying them on request.
	/// </summary>
	class System : public Updatable
	{
		// methods
	public:

		/// <summary>
		/// Initializes a new instance of the <see cref="System"/> class.
		/// </summary>
		/// <param name="engine">The <see cref="Engine"/> engine instance.</param>
		System(Engine *const engine);

		/// <summary>
		/// Virtual destructor.
		/// </summary>
		virtual ~System() override {};

		/// <summary>
		/// Called when an object of a Component type that has been claimed by this System (using Engine::SetManagingSystem) is created.
		/// </summary>
		/// <param name="srcEnt">The source Entity.</param>
		/// <param name="cmpType">The Component's type_index.</param>
		/// <returns>A const pointer to the created Component, stored internally by the System.</returns>
		virtual Component*const OnComponentCreate(Entity *const srcEnt, std::type_index cmpType);
		
		/// <summary>
		/// Called when an object of a Component type that has been claimed by this System (using Engine::SetManagingSystem) is destroyed.
		/// </summary>
		/// <param name="srcEnt">The source Entity.</param>
		/// <param name="cmpType">The Component's type_index.</param>
		/// <returns>True if the Component was successfully destroyed, false otherwise.</returns>
		virtual bool OnComponentDestroy(Entity *const srcEnt, Component *const srcCmp);
		
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
		/// Retrieves a unique Component identifier for a Component managed by this System.
		/// </summary>
		/// <returns>A unique component identifier.</returns>
		uint32_t GenerateUniqueComponentId();

		/// <summary>
		/// Retrieves a free slot from the System's handle table.
		/// </summary>
		/// <returns>The slot's index.</returns>
		uint32_t GetFreeHandleSlot();

		// members
	public:

		friend class Component;
		friend class Handle;

		Engine *const engine;

		uint32_t counter = 0;
		std::vector<Component *> handles;

	private:
	};

}

#endif // !_MAESTRO_SYSTEM_H_