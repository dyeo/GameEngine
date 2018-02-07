#ifndef _MAESTRO_ENTITY_H_
#define _MAESTRO_ENTITY_H_

#include "Composable.h"

class Entity : public Composable
{
public:

	virtual void CreateComponent() override;
	virtual void DestroyComponent() override;
	virtual void CreateEntity() override;
	virtual void DestroyEntity() override;

private:

};

#endif // !_MAESTRO_ENTITY_H_
