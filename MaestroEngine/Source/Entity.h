#ifndef _MAESTRO_ENTITY_H_
#define _MAESTRO_ENTITY_H_

#include "Component.h"

#include <unordered_map>

namespace mae
{

	/// <summary>
	/// A static Component that contains other components, and is the smallest object representable in a game Scene.
	/// </summary>
	class Entity : public Component
	{

		// methods
	public:

		Entity();
		virtual ~Entity() override {};

		// members
	public:

		const std::type_index Type;

	protected:

		friend Component;
		std::multimap<std::type_index, Component *const> components;

	private:
	};

}

#endif // !_MAESTRO_ENTITY_H_