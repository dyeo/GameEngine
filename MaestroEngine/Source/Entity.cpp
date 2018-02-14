#include "Entity.h"

#include "Maestro.h"
#include "Engine.h"
#include "Component.h"

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

}