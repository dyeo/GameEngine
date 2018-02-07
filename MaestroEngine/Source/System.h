#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Updatable.h"

#include <typeindex>

class Maestro;
class Component;
class Entity;

class System : public Updatable
{
public:

	System(Maestro *const engine);

	virtual Component*const OnComponentCreate(Entity *const srcEnt, std::type_index cmpType);
	virtual bool OnComponentDestroy(Entity *const srcEnt, Component *const srcCmp);

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

protected:

	Maestro *const engine;

private:
};

#endif // !_MAESTRO_SYSTEM_H_
