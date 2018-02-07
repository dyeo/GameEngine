#include "Entity.h"

#include "Maestro.h"

Entity::Entity()
	: Component(Maestro::GetManagingSystem<Entity>())
{

}