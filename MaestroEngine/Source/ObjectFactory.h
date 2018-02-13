#ifndef _MAESTRO_OBJECT_FACTORY_H_
#define _MAESTRO_OBJECT_FACTORY_H_

#include "Entity.h"

#include "EntityHandle.h"

#include <cstdint>
#include <vector>

namespace mae
{
	
	class ObjectFactory
	{
		// methods
	public:

		Entity *const CreateEntity();
		bool DestroyEntity(Entity *const srcEnt);
		bool DestroyEntity(EntityHandle srcHnd);

		uint32_t GetNextFreeIndex();
		uint32_t GetUniqueIdentifier();

		// members
	protected:

		friend EntityHandle;
				
		std::vector<Entity> entities;
		std::vector<Entity *> handles;

	private:

		static uint32_t counter;

	};

}

#endif // !_MAESTRO_OBJECT_FACTORY_H_
