#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Component.h"
#include "Entity.h"

#include <typeindex>

class System : public Updatable
{
public:

	virtual Component* OnComponentCreate(Entity *srcEnt, std::type_index cmpType);
	virtual bool OnComponentDestroy(Entity *srcEnt, Component *srcCmp);

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

private:
};

#endif // !_MAESTRO_SYSTEM_H_
