#include "Entity.h"

#include "Engine.h"

namespace mae
{

	Entity::Entity()
		: Component(system->engine->GetManagingSystem<Entity>(), this)
	{
		components = std::multimap<std::type_index, Component *const>();
	}

}