#include "EntityHandle.h"

#include "Maestro.h"
#include "Engine.h"
#include "ObjectFactory.h"

namespace mae
{
	EntityHandle::EntityHandle()
		: index(0)
		, uid(0)
	{

	}

	EntityHandle::EntityHandle(Entity * const entity)
		: index(entity->handleIndex)
		, uid(entity->handleUid)
	{
	}

	EntityHandle &EntityHandle::operator=(EntityHandle &other)
	{
		index = other.index;
		uid = other.uid;
		return *this;
	}

	EntityHandle &EntityHandle::operator=(Entity *const other)
	{
		index = other->handleIndex;
		uid = other->handleUid;
		return *this;
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
