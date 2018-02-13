#include "ObjectFactory.h"

#include <algorithm>

namespace mae
{
	uint32_t ObjectFactory::counter = 0;

	Entity *const ObjectFactory::CreateEntity()
	{
		Entity e;
		e.handleIndex = GetNextFreeIndex();
		e.handleUid = GetUniqueIdentifier();
		entities.push_back(e);
		return &e;
	}

	bool ObjectFactory::DestroyEntity(Entity * const srcEnt)
	{
		handles[srcEnt->handleIndex] = nullptr;
		auto it = std::find(entities.begin(), entities.end(), *srcEnt);
		if (it != entities.end())
		{
			entities.erase(it);
			return true;
		}
		return false;
	}

	bool ObjectFactory::DestroyEntity(EntityHandle srcHnd)
	{
		Entity *const srcEnt = handles[srcHnd.index];
		return DestroyEntity(srcEnt);
	}

	uint32_t ObjectFactory::GetNextFreeIndex()
	{
		auto it = std::find(handles.begin(), handles.end(), nullptr);
		return (it - handles.begin());
	}

	uint32_t ObjectFactory::GetUniqueIdentifier()
	{
		return ++counter;
	}

}