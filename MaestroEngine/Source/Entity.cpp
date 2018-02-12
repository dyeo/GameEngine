#include "Entity.h"

#include "Maestro.h"
#include "Engine.h"

namespace mae
{

	Entity::Entity()
		: Type(typeid(Entity))
		, Component(Maestro::GetEngine()->GetManagingSystem<Entity>(), this)
	{
		components = std::multimap<std::type_index, Component *const>();
	}

}