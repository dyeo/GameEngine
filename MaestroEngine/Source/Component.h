#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Maestro.h"

#include <typeinfo>
#include <typeindex>
#include <type_traits>

class Entity;

class Component : public Updatable
{
// methods
public:

	Component(System *const system, Entity *const entity);
	virtual ~Component() override {};

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
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

template<typename C>
inline C * const Component::GetComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
	std::type_index componentType = std::type_index(typeid(C));

	auto it = entity->components.find(componentType);
	Component *const component = (it == entity->components.end()) ? nullptr : it->second;
	return static_cast <C * const> (component);
}

template<typename C>
inline C * const Component::GetComponent(int cmpInd)
{
	static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
	std::type_index componentType = std::type_index(typeid(C));

	auto bucket = entity->components.equal_range(componentType);
	auto it = bucket->first + cmpInd;
	Component *const component = (it >= bucket->second) ? nullptr : it->second;
	return static_cast <C * const> (component);
}

template <typename C> inline C * const Component::CreateComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
	System *const managingSystem = Maestro::GetManagingSystem<C>();
	std::type_index componentType = std::type_index(typeid(C));

	Component *const component = managingSystem->OnComponentCreate(entity, componentType);
	entity->components.insert(std::make_pair(componentType, component));
	component->OnCreate();
	return static_cast <C * const> (component);
}

template <typename C> inline bool Component::DestroyComponent(C *const component)
{
	static_assert(std::is_base_of<Component, C>::value, "C does not inherit Component.");
	System *const managingSystem = Maestro::GetManagingSystem<C>();
	std::type_index componentType = std::type_index(typeid(C));
	
	auto iters = entity->components.equal_range(entity->components.find(componentType));
	for (auto it = iters->first; it != iters->second; it++)
	{
		if (component == &(*it))
		{
			static_cast<Component *const>(component)->OnDestroy();
			entity.erase(it);
			return;
		}
	}
	bool destroyResult = managingSystem->OnComponentDestroy(entity, component);
	return destroyResult;
}

#endif // !_MAESTRO_COMPONENT_H_
