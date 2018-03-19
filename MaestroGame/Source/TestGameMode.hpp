#pragma once

#define MAESTRO_DEBUG

#include <Maestro.h>
#include <Engine.h>
#include <GameMode.h>
#include <Entity.h>
#include <EntityHandle.h>
#include <Logging.h>
#include <Sprite.h>

#include <SFML/Graphics.hpp>

class TestGameMode : public mae::GameMode
{
public:

	TestGameMode()
	{

	}

	virtual inline void OnCreate() override
	{
	}

	virtual inline void OnStart() override
	{
		const char *texStr = "./Assets/orb.png";
		if (!tex.loadFromFile(texStr))
		{
			LOG_ERROR("Texture %s not supported.", texStr);
			assert(0);
		}

		ent1 = CreateEntity();
		
		mae::Sprite *const s1 = ent1->AddComponent<mae::Sprite>();
		s1->setTexture(tex);

		ent2 = CreateEntity();

		mae::Sprite *const s2 = ent2->AddComponent<mae::Sprite>();
		s2->setTexture(tex);
		
		ent1->transform->SetPosition(gm::vec3(100, 100, 0));

		ent1->transform->SetParent(ent2->transform);

		ent2->transform->SetPosition(gm::vec3(50, 50, 0));
		
		ent1->transform->SetScale(gm::vec3(10, 10, 1));

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

	sf::Texture tex;

	mae::EntityHandle ent1;
	mae::EntityHandle ent2;	
};
