#include "GameMode.h"

#include "Engine.h"
#include "Maestro.h"
#include "ObjectFactory.h"

namespace mae
{
	GameMode::GameMode()
	{
	}

	void GameMode::OnCreate()
	{
	}

	void GameMode::OnStart()
	{
	}

	void GameMode::OnUpdate()
	{
	}

	void GameMode::OnFixedUpdate()
	{
	}

	void GameMode::OnRender()
	{
	}

	void GameMode::OnFinish()
	{
	}

	void GameMode::OnDestroy()
	{
	}

	EntityHandle GameMode::CreateEntity()
	{
		return Maestro::GetEngine()->objectFactory.CreateEntity();
	}

	bool GameMode::DestroyEntity(EntityHandle ent)
	{
		return Maestro::GetEngine()->objectFactory.DestroyEntity(ent);
	}
}
