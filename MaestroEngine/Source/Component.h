#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Engine.h"

#include "EntityHandle.h"

#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

namespace mae
{
	class Entity;
		
	/// <summary>
	/// Components are discrete buckets of data and functionality associated with an Entity. 
	/// Component types are claimed by a System, and the System manages their creation, updating, and destruction.
	/// </summary>
	class Component : public Updatable
	{
		// methods
	public:

		Component(System *const system, EntityHandle entity);
		virtual ~Component() override;
		
		/// <summary>
		/// Called once when the Component is created, before OnStart or OnUpdate.
		/// </summary>
		virtual void OnCreate() override;
		
		/// <summary>
		/// Called once during the update loop for this Component, before the first OnUpdate.
		/// </summary>
		virtual void OnStart() override;
		
		/// <summary>
		/// Called during the update loop for this Component, and is called at least once per frame.
		/// </summary>
		virtual void OnUpdate() override;
		
		/// <summary>
		/// Called once per physics frame for this Updatadable.
		/// </summary>
		virtual void OnFixedUpdate() override;

		/// <summary>
		/// Called following OnUpdate for this Component, and is called as many times as possible per frame (or once per frame if vsync is enabled).
		/// </summary>
		virtual void OnRender() override;
		
		/// <summary>
		/// Called once after the update loop for this Component, before any Component in this object's update loop are destroyed.
		/// </summary>
		virtual void OnFinish() override;		

		/// <summary>
		/// Called after OnFinish for this Component, before the object is destroyed.
		/// </summary>
		virtual void OnDestroy() override;

		/// <summary>
		/// Gets the first Component of this type from this Component's Entity.
		/// </summary>
		/// <returns>The Component if it exists, or nullptr otherwise.</returns>
		template <typename C> Component *const GetComponent();
		Component *const GetComponent(std::type_index cmpType);

		/// <summary>
		/// Gets the first Component of this type from this Component's Entity.
		/// </summary>
		/// <param name="mpInd">The order of the Components of the current type, ranging from 0-n, where 0 is the first created Component and n is the last.</param>
		/// <returns>The Component if it exists, or nullptr otherwise.</returns>
		template <typename C> Component *const GetComponent(int cmpInd);
		Component *const GetComponent(int cmpInd, std::type_index cmpType);

		/// <summary>
		/// Creates a Component and assigns it to its respective System to be updated by the Engine.
		/// </summary>
		/// <returns>The created Component, or nullptr if the Component could not be created.</returns>
		template <typename C> Component *const CreateComponent();
		Component *const CreateComponent(std::type_index cmpType);

		/// <summary>
		/// Removes a Component from its respective Saystem and destroys it.
		/// </summary>
		/// <param name="component">The component to be destroyed.</param>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		template <typename C> bool DestroyComponent(Component *const cmp);
		bool DestroyComponent(Component *const cmp, std::type_index cmpType);

		/// <summary>
		/// Creates an Entity and adds it to the update loop.
		/// </summary>
		/// <returns>The Entity that was created.</returns>
		Entity *const CreateEntity();

		/// <summary>
		/// Removes the Entity from the update loop and destroys it.
		/// </summary>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		bool DestroyEntity(Entity *const ent);
		
		// members
	public:

		EntityHandle entity;
		System *const system;

	private:
		
		uint32_t uniqueId;
		uint32_t handleIndex;

	};

	template <typename C> Component *const Component::GetComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return GetComponent(cmpType);
	}

	template <typename C> Component *const Component::GetComponent(int cmpInd)
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return GetComponent(cmpInd, cmpType);
	}

	template <typename C> inline Component *const Component::CreateComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return CreateComponent(cmpType);
	}

	template <typename C> inline bool Component::DestroyComponent(Component *const component)
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return DestroyComponent(component, cmpType);
	}

}

#endif // !_MAESTRO_COMPONENT_H_