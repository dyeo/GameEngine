#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Updatable.h"
#include "System.h"

#include <assert.h>

class Entity;

class Component : public Updatable
{
public:

	Component(System *const system, Entity *const entity);

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;
	
	/// <summary>
	/// Creates a component and assigns it to its respective system to be updated by the engine.
	/// </summary>
	/// <returns>A const-pointer to the created component, or nullptr if the component could not be created.</returns>
	template <typename C> C *const CreateComponent();

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
	bool DestroyEntity(Entity *const ent);

protected:

	System *const system;
	Entity *const entity;

private:
};

template <typename C> inline C * const Component::CreateComponent()
{
	std::static_assert<
	System *const managingSystem = Maestro::GetManagingSystem<C>();
	return managingSystem->OnComponentCreate(entity, std::type_index(typeid(C)));
}

template <typename C> inline bool Component::DestroyComponent(C *const component)
{
	System *const managingSystem = Maestro::GetManagingSystem<C>();
	return managingSystem->OnComponentDestroy(entity, component);
}

#endif // !_MAESTRO_COMPONENT_H_
