#include "Entity.h"

#include "Engine.h"

namespace mae
{

	Entity::Entity()
		: Component(Engine::GetManagingSystem<Entity>(), this)
	{
		components = std::multimap<std::type_index, Component *const>();
	}

}