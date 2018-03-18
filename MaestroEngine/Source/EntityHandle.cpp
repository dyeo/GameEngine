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

	EntityHandle::EntityHandle(Entity * const GetEntity)
		: index(GetEntity->handleIndex)
		, uid(GetEntity->handleUid)
	{
	}

	EntityHandle & EntityHandle::operator=(EntityHandle &other)
	{
		index = other.index;
		uid = other.uid;
		return *this;
	}

	EntityHandle & EntityHandle::operator=(Entity * const other)
	{
		index = other->handleIndex;
		uid = other->handleUid;
		return *this;
	}

	bool EntityHandle::operator==(const EntityHandle &other)
	{
		return uid == other.uid;
	}

	Entity * EntityHandle::operator->()
	{
		return GetEntity();
	}

	Entity * EntityHandle::GetEntity()
	{
		Engine *const engine = Maestro::GetEngine();
		Entity *entity = engine->objectFactory.handles[index];
		return entity;
	}
}
