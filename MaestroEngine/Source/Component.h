#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Updatable.h"

class System;

class Component : public Updatable
{
public:

	Component(System *const system);

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

	void CreateComponent();
	void DestroyComponent();
	void CreateEntity();
	void DestroyEntity();

protected:

	System *const system;

private:
};

#endif // !_MAESTRO_COMPONENT_H_
