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
		tex.loadFromFile("./Assets/orb.png");

		ent1 = CreateEntity();
		
		ent2 = CreateEntity();

		mae::Sprite *const s1 = ent1->AddComponent<mae::Sprite>();
		s1->sprite = sf::Sprite(tex); 

		mae::Sprite *const s2 = ent2->AddComponent<mae::Sprite>();
		s2->sprite = sf::Sprite(tex);
		
		ent1->transform->SetLocalPosition(gm::vec3(0, 0, 0));
		ent2->transform->SetLocalPosition(gm::vec3(0.5f, 0.5f, 0));
		
		ent1->transform->SetLocalScale(gm::vec3(1, 1, 1));

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
