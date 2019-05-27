#include "ObjectFactory.h"
#include "Transform.h"

#include <algorithm>

namespace mae
{
	uint32_t ObjectFactory::counter = 0;

	ObjectFactory::ObjectFactory()
	{
		entities.reserve(65535);
		handles.reserve(65535);
	}

	EntityHandle ObjectFactory::CreateEntity()
	{
		Entity e;
		entities.push_back(e);
		entities.back().handleUid = GetUniqueIdentifier();
		entities.back().handleIndex = GetNextFreeIndex();
		handles.push_back(&(entities.back()));
		handles.back()->transform = handles.back()->AddComponent<Transform>();

		return EntityHandle(handles.back());
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
		return handles.size();
		// auto it = std::find(handles.begin(), handles.end(), nullptr);
		// return (it - handles.begin());
	}

	uint32_t ObjectFactory::GetUniqueIdentifier()
	{
		return ++counter;
	}

}
