#include "Component.h"

#include "Maestro.h"
#include "System.h"
#include "Entity.h"

#include <iterator>

namespace mae
{

	Component::Component(System *const system, EntityHandle entity)
		: system(system)
		, entity(entity)
	{
	}

	Component::~Component()
	{
	}

	void Component::OnCreate()
	{		
	}

	void Component::OnStart()
	{
	}

	void Component::OnUpdate()
	{
	}

	void Component::OnFixedUpdate()
	{
	}

	void Component::OnRender()
	{
	}

	void Component::OnFinish()
	{
	}

	void Component::OnDestroy()
	{
	}

	EntityHandle Component::CreateEntity()
	{
		return Maestro::GetEngine()->objectFactory.CreateEntity();
	}

	bool Component::DestroyEntity(EntityHandle ent)
	{
		return Maestro::GetEngine()->objectFactory.DestroyEntity(ent);
	}

}
