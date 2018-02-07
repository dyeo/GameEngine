#include "System.h"
#include "Maestro.h"
#include "Component.h"

System::System(Maestro *const engine)
	: engine(engine)
{
}

Component * const System::OnComponentCreate(Entity *const srcEnt, std::type_index cmpType)
{
	return nullptr;
}

bool System::OnComponentDestroy(Entity *const srcEnt, Component *const srcCmp)
{
	return false;
}

void System::OnCreate()
{
}

void System::OnStart()
{
}

void System::OnUpdate()
{
}

void System::OnRender()
{
}

void System::OnFinish()
{
}

void System::OnDestroy()
{
}