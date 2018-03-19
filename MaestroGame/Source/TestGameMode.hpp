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
		
		ent2->transform->SetParent(ent1->transform);

		ent1->transform->SetPosition(gm::vec3(50, 50, 0));
		
		ent2->transform->SetPosition(gm::vec3(50, 50, 0));
		

	}

	virtual inline void OnUpdate() override
	{
		float dt = 128 * mae::Maestro::GetEngine()->deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			ent1->transform->Translate(gm::vec3::right() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			ent1->transform->Translate(gm::vec3::left() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			ent1->transform->Translate(gm::vec3::down() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			ent1->transform->Translate(gm::vec3::up() * dt);
		}
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
