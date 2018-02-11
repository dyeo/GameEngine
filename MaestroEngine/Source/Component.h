#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Engine.h"

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

		Component(System *const system, Entity *const entity);
		virtual ~Component() override {};
		
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
		/// Gets the first component of this type from this component's entity.
		/// </summary>
		/// <returns>A const-pointer to the component if it exists, or nullptr otherwise.</returns>
		template <typename C> C * const GetComponent();

		/// <summary>
		/// Gets the first component of this type from this component's entity.
		/// </summary>
		/// <param name="mpInd">The order of the Components of the current type, ranging from 0-n, where 0 is the first created Component and n is the last.</param>
		/// <returns>A const-pointer to the component if it exists, or nullptr otherwise.</returns>
		template <typename C> C * const GetComponent(int cmpInd);

		/// <summary>
		/// Creates a component and assigns it to its respective system to be updated by the engine.
		/// </summary>
		/// <returns>A const-pointer to the created component, or nullptr if the component could not be created.</returns>
		template <typename C> C * const CreateComponent();

		/// <summary>
		/// Removes a component from its respective system and destroys it.
		/// </summary>
		/// <param name="component">The component to be destroyed.</param>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		template <typename C> bool DestroyComponent(C *const cmp);

		/// <summary>
		/// Creates an entity and adds it to the update loop.
		/// </summary>
		/// <returns>The entity that was created.</returns>
		Entity *const CreateEntity();

		/// <summary>
		/// Removes the entity from the update loop and destroys it.
		/// </summary>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		bool DestroyEntity(Entity * const ent);

		// members
	public:

		Entity *const entity;

	protected:

		System *const system;

	private:
	};

	template <typename C> inline C * const Component::GetComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
		std::type_index componentType = std::type_index(typeid(C));

		auto it = entity->components.find(componentType);
		Component *const component = (it == entity->components.end()) ? nullptr : it->second;
		return static_cast <C * const> (component);
	}

	template <typename C> inline C * const Component::GetComponent(int cmpInd)
	{
		static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
		std::type_index componentType = std::type_index(typeid(C));

		auto bucket = entity->components.equal_range(componentType);
		auto it = bucket.first + cmpInd;
		Component *const component = (it >= bucket.second) ? nullptr : it->second;
		return static_cast <C * const> (component);
	}

	template <typename C> inline C * const Component::CreateComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
		System *const managingSystem = system->engine->GetManagingSystem<C>();
		std::type_index componentType = std::type_index(typeid(C));

		Component *const component = managingSystem->OnComponentCreate(entity, componentType);
		entity->components.insert(std::make_pair(componentType, component));
		component->OnCreate();
		return static_cast <C * const> (component);
	}

	template <typename C> inline bool Component::DestroyComponent(C *const component)
	{
		static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
		System *const managingSystem = system->engine->GetManagingSystem<C>();
		std::type_index componentType = std::type_index(typeid(C));

		auto bucket = entity->components.equal_range(componentType);
		for (auto it = bucket.first; it != bucket.second; ++it)
		{
			if (component == it->second)
			{
				static_cast<Component *const>(component)->OnDestroy();
				entity->components.erase(it);
				break;
			}
		}
		return managingSystem->OnComponentDestroy(entity, component);
	}

}

#endif // !_MAESTRO_COMPONENT_H_