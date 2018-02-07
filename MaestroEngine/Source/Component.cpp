#include "Component.h"

#include "System.h"

Component::Component(System *const system)
	: system(system)
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

void Component::CreateComponent()
{
}

void Component::DestroyComponent()
{
}

void Component::CreateEntity()
{
}

void Component::DestroyEntity()
{
}