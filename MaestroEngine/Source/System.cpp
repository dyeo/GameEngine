#include "System.h"
#include "Maestro.h"

System::System(Maestro *const engine)
	: engine(engine)
{
}

Component * System::OnComponentCreate(Entity * srcEnt, std::type_index cmpType)
{
	return nullptr;
}

bool System::OnComponentDestroy(Entity * srcEnt, Component * srcCmp)
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