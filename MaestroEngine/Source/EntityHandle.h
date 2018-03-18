#ifndef _MAESTRO_ENTITYHANDLE_HPP_
#define _MAESTRO_ENTITYHANDLE_HPP_

#include <cstdint>

namespace mae
{
	class Entity;

	class EntityHandle
	{
		// methods
	public:

		EntityHandle();

		EntityHandle(Entity *const GetEntity);

		EntityHandle &operator=(EntityHandle &other);

		EntityHandle &operator=(Entity *const other);
		
		bool operator==(const EntityHandle &other);

		Entity *operator->();

		Entity *GetEntity();

	private:
		
		// members
	public:

		uint32_t index;
		uint32_t uid;

	private:
	};

}

#endif // !_MAESTRO_ENTITYHANDLE_HPP_
