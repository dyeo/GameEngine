#pragma once

#define MAESTRO_DEBUG

#include <Maestro.h>
#include <Engine.h>
#include <GameMode.h>
#include <Entity.h>
#include <EntityHandle.h>
#include <Logging.h>
#include <Sprite.h>
#include "RigidBody.h"
#include <Music.h>
#include <Sound.h>

#include <SFML/Graphics.hpp>

using namespace mae;

class TestGameMode : public GameMode
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
			LOG_ERROR("Texture %s does not exist.", texStr);
			assert(0);
		}

		const char *sndStr = "./Assets/sound.ogg";
		if (!snd.loadFromFile(sndStr))
		{
			LOG_ERROR("Sound file %s does not exist.", texStr);
			assert(0);
		}

		ent1 = CreateEntity();
		
		Sprite *const s1 = ent1->AddComponent<Sprite>();
		Sound *const a1 = ent1->AddComponent<Sound>();
		RigidBody *const r1 = ent1->AddComponent<RigidBody>();
		s1->setTexture(tex);
		a1->setBuffer(snd);
		a1->setVolume(100);

		const char *musStr = "./Assets/theme.ogg";

		/*ent2 = CreateEntity();

		Sprite *const s2 = ent2->AddComponent<Sprite>();
		Music *const a2 = ent2->AddComponent<Music>();
		RigidBody *const r2 = ent2->AddComponent<RigidBody>();
		r2->UseGravity = false;
		s2->setTexture(tex);
		if (!a2->openFromFile(musStr))
		{
			LOG_ERROR("Music file ", texStr, " does not exist.");
			assert(0);
		}

		a2->setVolume(50);
		a2->play();
		
		ent2->transform->SetParent(ent1->transform);*/

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

		Sound *s1 = ent1->GetComponent<Sound>();
		if (s1->getStatus() != Sound::Status::Playing && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			s1->play();
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
	sf::SoundBuffer snd;

	mae::EntityHandle ent1;
	mae::EntityHandle ent2;	
};
