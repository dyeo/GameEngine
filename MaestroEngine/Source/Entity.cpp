#include "Entity.h"

#include "Maestro.h"
#include "Engine.h"
#include "Component.h"
#include "Transform.h"

namespace mae
{

	Entity::Entity()
	{
	}

	bool Entity::operator==(const Entity &other)
	{
		return handleUid == other.handleUid;
	}

	Component *const Entity::GetComponent(std::type_index cmpType)
	{
		auto it = components.find(cmpType);

		Component *const component = (it == components.end()) ? nullptr : it->second;

		return component;
	}

	Component *const Entity::GetComponent(int cmpInd, std::type_index cmpType)
	{
		auto bucket = components.equal_range(cmpType);
		auto it = bucket.first;
		std::advance(it, cmpInd);

		Component *const component = (it == bucket.second) ? nullptr : it->second;

		return component;
	}

	Component *const Entity::AddComponent(std::type_index cmpType)
	{
		System *const managingSystem = Maestro::GetEngine()->GetManagingSystem(cmpType);

		Component *const component = managingSystem->OnComponentCreate(this, cmpType);
		components.insert(std::make_pair(cmpType, component));
		component->OnCreate();

		//printf("Entity::AddComponent(%s) -> %p\n", name, cmpType.name(), component);
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
				components.erase(it--);
				break;
			}
		}

		return managingSystem->OnComponentDestroy(this, component);
	}

}