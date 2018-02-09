#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Updatable.h"

#include <typeindex>

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
		/// Called when a new <see cref="Component"/> that has been claimed by this <see cref="System"/> (using <see cref="Engine::SetManagingSystem" />) is requested by a Component or <see cref="Entity"/>.
		/// </summary>
		/// <param name="srcEnt">The source Entity.</param>
		/// <param name="cmpType">The Component's type_index.</param>
		/// <returns>A const pointer to the created Component, stored internally by the System.</returns>
		virtual Component*const OnComponentCreate(Entity *const srcEnt, std::type_index cmpType);
		virtual bool OnComponentDestroy(Entity *const srcEnt, Component *const srcCmp);

		virtual void OnCreate() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;
		virtual void OnFinish() override;
		virtual void OnDestroy() override;

		// members
	protected:

		Engine *const engine;

	private:
	};

}

#endif // !_MAESTRO_SYSTEM_H_
