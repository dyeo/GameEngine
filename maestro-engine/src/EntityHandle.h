#ifndef _MAESTRO_ENTITYHANDLE_H_
#define _MAESTRO_ENTITYHANDLE_H_

#include <cstdint>

namespace mae
{
	class Entity;

	class EntityHandle
	{
		// methods
	public:

		EntityHandle();

		EntityHandle(Entity *const entity);

		EntityHandle &operator=(EntityHandle &other);

		EntityHandle &operator=(Entity *const other);
		
		bool operator==(const EntityHandle &other);

		Entity *operator->();

		Entity *entity();

	private:
		
		// members
	public:

		uint32_t index;
		uint32_t uid;

	private:
	};

}

#endif // !_MAESTRO_ENTITYHANDLE_H_
