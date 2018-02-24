#include "EntityHandle.h"

#include "Maestro.h"
#include "Engine.h"
#include "ObjectFactory.h"

namespace mae
{
	EntityHandle::EntityHandle(Entity * const entity)
		: index(entity->handleIndex)
		, uid(entity->handleUid)
	{
	}

	EntityHandle &EntityHandle::operator=(Entity *const other)
	{
		return EntityHandle(other);
	}

	bool EntityHandle::operator==(const EntityHandle &other)
	{
		return uid == other.uid;
	}

	bool EntityHandle::operator==(const Entity &other)
	{
		return uid == other.handleUid;
	}

	Entity& EntityHandle::operator*()
	{
		return *Maestro::GetEngine()->objectFactory.handles[index];
	}

	Entity* EntityHandle::operator->()
	{
		return Maestro::GetEngine()->objectFactory.handles[index];
	}
}