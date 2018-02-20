#ifndef _MAESTRO_ENTITYHANDLE_HPP_
#define _MAESTRO_ENTITYHANDLE_HPP_

#include "Entity.h"

#include <cstdint>

namespace mae
{

	class EntityHandle
	{
		// methods
	public:

		EntityHandle(Entity *const entity);

		EntityHandle &operator=(EntityHandle &other) = default;
		
		bool operator==(const EntityHandle &other);

		bool operator==(const Entity &other);

		Entity& operator*();

		Entity* operator->();

	private:
		
		// members
	public:

		const uint32_t index;
		const uint32_t uid;

	private:
	};

}

#endif // !_MAESTRO_ENTITYHANDLE_HPP_
