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

	Component *const Component::GetComponent(std::type_index cmpType)
	{
		auto it = entity->components.find(cmpType);
		Component *const component = (it == entity->components.end()) ? nullptr : it->second;

		return component;
	}

	Component *const Component::GetComponent(int cmpInd, std::type_index cmpType)
	{
		auto bucket = entity->components.equal_range(cmpType);
		auto it = bucket.first;
		std::advance(it, cmpInd);

		Component *const component = (it != bucket.second) ? nullptr : it->second;

		return component;
	}

	Component *const Component::CreateComponent(std::type_index cmpType)
	{
		System *const managingSystem = Maestro::GetEngine()->GetManagingSystem(cmpType);

		Component *const component = managingSystem->OnComponentCreate(entity, cmpType);
		entity->components.insert(std::make_pair(cmpType, component));
		component->OnCreate();
		return component;
	}

	bool Component::DestroyComponent(Component *const component, std::type_index cmpType)
	{
		System *const managingSystem = Maestro::GetEngine()->GetManagingSystem(cmpType);
		
		auto bucket = entity->components.equal_range(cmpType);
		for (auto it = bucket.first; it != bucket.second; ++it)
		{
			if (component == it->second)
			{
				component->OnDestroy();
				entity->components.erase(it);
				break;
			}
		}

		return managingSystem->OnComponentDestroy(entity, component);
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