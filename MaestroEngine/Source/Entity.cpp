#include "Entity.h"

#include "Maestro.h"

Entity::Entity()
	: Component(Maestro::GetManagingSystem<Entity>(), this)
{
	components = std::unordered_map<std::type_index, Component *const>();
}