#include "Component.h"

#include "System.h"
#include "Entity.h"

namespace mae
{

	Component::Component(System *const system, Entity *const entity)
		: Type(typeid(*this))
		, system(system)
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

	Handle Component::GetComponent(std::type_index cmpType)
	{
		auto it = entity->components.find(cmpType);
		Handle component = (it == entity->components.end()) ? nullptr : it->second;

		return component;
	}

	Handle Component::GetComponent(int cmpInd, std::type_index cmpType)
	{
		auto bucket = entity->components.equal_range(cmpType);
		auto it = bucket.first + cmpInd;
		Handle component = (it >= bucket.second) ? nullptr : it->second;

		return component;
	}

	bool Component::CreateComponent(std::type_index cmpType)
	{
		System *const managingSystem = system->engine->GetManagingSystem(cmpType);
		Entity *const ent = *entity;
		Handle component = managingSystem->OnComponentCreate(ent, cmpType);
		entity->components.insert(std::make_pair(cmpType, (*component)));
		component->OnCreate();
		return component;
	}

	bool Component::DestroyComponent(Handle cmp, std::type_index cmpType)
	{
		System *const managingSystem = system->engine->GetManagingSystem(cmpType);

		entity->OnUpdate();

		auto bucket = entity->components.equal_range(cmpType);
		for (auto it = bucket.first; it != bucket.second; ++it)
		{
			if (component == Handle(it->second))
			{
				component->OnDestroy();
				entity->components.erase(it);
				break;
			}
		}

		return managingSystem->OnComponentDestroy(entity, component);
	}

	Handle Component::CreateEntity()
	{
		return CreateComponent<Entity>();
	}

	bool Component::DestroyEntity(Handle ent)
	{
		return DestroyComponent<Entity>(ent);
	}



}