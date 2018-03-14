#include "ObjectFactory.h"
#include "Transform.h"

#include <algorithm>

namespace mae
{
	uint32_t ObjectFactory::counter = 0;

	ObjectFactory::ObjectFactory()
		: entities()
		, handles()
	{
	}

	EntityHandle ObjectFactory::CreateEntity()
	{
		entities.push_back(Entity());
		entities.back().handleIndex = GetNextFreeIndex();
		entities.back().handleUid = GetUniqueIdentifier();
		handles.push_back(&(entities.back()));

		entities.back().AddComponent<Transform>();

		return EntityHandle(&entities.back());
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