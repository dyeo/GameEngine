#ifndef _MAESTRO_ENTITY_H_
#define _MAESTRO_ENTITY_H_

#include "Component.h"

#include <unordered_map>

class Entity : public Component
{
public:

	Entity();

protected:

	friend Component;
	std::unordered_map<std::type_index, Component *const> components;

private:
};

#endif // !_MAESTRO_ENTITY_H_
