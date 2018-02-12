#include "System.h"
#include "Engine.h"
#include "Component.h"

namespace mae
{

	System::System(Engine *const engine)
		: engine(engine)
		, handles()
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

	void System::OnFixedUpdate()
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

	uint32_t System::GenerateUniqueComponentId()
	{
		return ++counter;
	}

	uint32_t System::GetFreeHandleSlot()
	{
		return (std::find(handles.begin(), handles.end(), nullptr) - handles.begin());
	}

}