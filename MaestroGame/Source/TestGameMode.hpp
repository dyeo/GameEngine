#pragma once

#include <Maestro.h>
#include <Engine.h>
#include <GameMode.h>
#include <EntityHandle.h>

class TestGameMode : public mae::GameMode
{
public:

	TestGameMode()
		: ent1(CreateEntity())
		, ent2(CreateEntity())
	{

	}

	virtual inline void OnCreate() override
	{
		mae::Transform * t1 = static_cast<mae::Transform*>(ent1->GetComponent<mae::Transform>());
		mae::Transform * t2 = static_cast<mae::Transform*>(ent2->GetComponent<mae::Transform>());

		t2->SetParent(t1);
	}

	virtual inline void OnStart() override
	{
	}

	virtual inline void OnUpdate() override
	{

	}

	virtual inline void OnFixedUpdate() override
	{

	}

	virtual inline void OnRender() override
	{

	}

	virtual inline void OnFinish() override
	{

	}

	virtual inline void OnDestroy() override
	{

	}

private:

	mae::EntityHandle ent1;
	mae::EntityHandle ent2;

	mae::Transform *t1;
	mae::Transform *t2;

};
