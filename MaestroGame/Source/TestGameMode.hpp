#pragma once

#define MAESTRO_DEBUG

#include <Maestro.h>
#include <Engine.h>
#include <GameMode.h>
#include <Entity.h>
#include <EntityHandle.h>
#include <Logging.h>

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
		ent1 = CreateEntity();

		ent2 = CreateEntity();

		mae::Entity *const tEnt1 = ent1.GetEntity();

		ent2->transform->SetParent(ent1->transform);

		ent1->transform->SetLocalPosition(gm::vec3(0, 0, 0));
		ent2->transform->SetLocalPosition(gm::vec3(0.5f, 0.5f, 0.5f));
		
		ent1->transform->SetLocalScale(gm::vec3(1, 1, 1));

		tex.loadFromFile("./Assets/orb.png");
		s1 = sf::Sprite(tex); //s2 = sf::Sprite(tex);
		s2 = sf::Sprite(tex); //s2 = sf::Sprite(tex);
	}

	virtual inline void OnUpdate() override
	{
		s1.setPosition(ent1->transform->GetLocalPosition().x, ent1->transform->GetLocalPosition().y);
		s2.setPosition(ent2->transform->GetLocalPosition().x, ent2->transform->GetLocalPosition().y);
	}

	virtual inline void OnFixedUpdate() override
	{

	}

	virtual inline void OnRender() override
	{
		mae::Maestro::GetEngine()->window.draw(s1);
		mae::Maestro::GetEngine()->window.draw(s2);
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

	sf::Texture tex;
	sf::Sprite s1;
	sf::Sprite s2;

};
