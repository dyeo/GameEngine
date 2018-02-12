#include "Component.h"

#include "System.h"
#include "Entity.h"

namespace mae
{

	Component::Component(System *const system, Entity *const entity)
		: system(system)
		, entity(entity)
	{
		uniqueId = system->GenerateUniqueComponentId();
		handleIndex = system->GetFreeHandleSlot();
		if (handleIndex == system->handles.size())
		{
			system->handles.push_back(this);
		}
		else
		{
			system->handles[handleIndex] = this;
		}
	}

	Component::~Component()
	{
		system->handles[handleIndex] = nullptr;
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

	Entity *const Component::CreateEntity()
	{
		return CreateComponent<Entity>();
	}

	bool Component::DestroyEntity(Entity *const ent)
	{
		return DestroyComponent<Entity>(ent);
	}

}