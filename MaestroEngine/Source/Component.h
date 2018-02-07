#ifndef _MAESTRO_COMPONENT_H_
#define _MAESTRO_COMPONENT_H_

#include "Updatable.h"
#include "Composable.h"

class Component : public Updatable, public Composable
{
public:

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

	virtual void CreateComponent() override;
	virtual void DestroyComponent() override;
	virtual void CreateEntity() override;
	virtual void DestroyEntity() override;

private:
};

#endif // !_MAESTRO_COMPONENT_H_
