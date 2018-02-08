#include "Entity.h"

#include "Maestro.h"

Entity::Entity()
	: Component(Maestro::GetManagingSystem<Entity>(), this)
{
	components = std::multimap<std::type_index, Component *const>();
}