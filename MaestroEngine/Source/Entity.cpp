#include "Entity.h"

#include "Maestro.h"
#include "Engine.h"
#include "Component.h"
#include "Transform.h"

namespace mae
{

	Entity::Entity()
		: components()
	{
	}

	bool Entity::operator==(const Entity &other)
	{
		return handleUid == other.handleUid;
	}

	Component *const Entity::GetComponent(std::type_index cmpType)
	{
		//using const_ref = std::multimap<std::type_index, Component *const>::const_reference;
		//auto it = std::find_if(components.begin(), components.end(), [&](const_ref pair) -> bool { return pair.first == cmpType; });

		return GetComponent(0, cmpType);
	}

	Component *const Entity::GetComponent(int cmpInd, std::type_index cmpType)
	{
		auto bucket = components.equal_range(cmpType);
		auto it = bucket.first;
		std::advance(it, cmpInd);

		Component *const component = (it != bucket.second) ? nullptr : it->second;

		return component;
	}

	Component *const Entity::AddComponent(std::type_index cmpType)
	{
		System *const managingSystem = Maestro::GetEngine()->GetManagingSystem(cmpType);

		Component *const component = managingSystem->OnComponentCreate(this, cmpType);
		components.insert(std::make_pair(cmpType, component));
		component->OnCreate();
		return component;
	}

	bool Entity::RemoveComponent(Component *const component, std::type_index cmpType)
	{
		System *const managingSystem = Maestro::GetEngine()->GetManagingSystem(cmpType);

		auto bucket = components.equal_range(cmpType);
		for (auto it = bucket.first; it != bucket.second; ++it)
		{
			if (component == it->second)
			{
				component->OnDestroy();
				components.erase(it);
				break;
			}
		}

		return managingSystem->OnComponentDestroy(this, component);
	}

}