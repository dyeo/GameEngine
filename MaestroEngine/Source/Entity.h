#ifndef _MAESTRO_ENTITY_H_
#define _MAESTRO_ENTITY_H_

#include <map>
#include <typeindex>

namespace mae
{
	class Component;

	/// <summary>
	/// A static Component that contains other components, and is the smallest object representable in a game Scene.
	/// </summary>
	class Entity
	{
		// methods
	public:

		bool operator==(const Entity &other);
		
	private:

		Entity();
		
		// members
	public:

		const char *name = "New Entity";

		friend Component;
		friend class EntityHandle;
		friend class ObjectFactory;
		
		std::multimap<std::type_index, Component *const> components;

		uint32_t handleIndex;
		uint32_t handleUid;

	private:
	};

}

#endif // !_MAESTRO_ENTITY_H_