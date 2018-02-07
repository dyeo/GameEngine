#include "Component.h"

#include "System.h"

Component::Component(System *const system, Entity *const entity)
	: system(system)
	, entity(entity)
{

}

void Component::OnCreate()
{
}

void Component::OnStart()
{
}

void Component::OnUpdate()
{
}

void Component::OnRender()
{
}

void Component::OnFinish()
{
}

void Component::OnDestroy()
{
}

void Component::CreateEntity()
{
}

void Component::DestroyEntity()
{
}