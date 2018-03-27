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
#include <iostream>

using namespace mae;

class TestGameMode : public GameMode
{
public:

	float counter = 0.0f;

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

		const char *brickTexStr = "./Assets/brick.png";
		if(!brickTex.loadFromFile(brickTexStr))
		{
			if (!tex.loadFromFile(texStr))
			{
				LOG_ERROR("Texture %s does not exist.", brickTexStr);
				assert(0);
			}
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
		ent3->GetComponent<RigidBody>()->bounciness = 1.0f;
		ent3->GetComponent<RigidBody>()->mass = 0.8f;
		r1->UseGravity = false;
		//std::cout << "position after adding RB" << ent1->transform->GetPosition() << std::endl;
		s1->setTexture(tex);
		a1->setBuffer(snd);
		a1->setVolume(100);

		const char *musStr = "./Assets/theme.ogg";

		ent2 = CreateEntity();

		Sprite *const s2 = ent2->AddComponent<Sprite>();
		Music *const a2 = ent2->AddComponent<Music>();
		s2->setTexture(tex);
		if (!a2->openFromFile(musStr))
		{
			LOG_ERROR("Music file ", texStr, " does not exist.");
			assert(0);
		}

		a2->setVolume(50);
		a2->play();

		ent3 = CreateEntity();

		Sprite *const s3 = ent3->AddComponent<Sprite>();
		RigidBody *const r3 = ent3->AddComponent<RigidBody>();
		s3->setTexture(brickTex);
		//s3->setTextureRect(sf::IntRect(0, 0, 30, 30));
		//s3->setScale(0.25f, 0.25f);

		ent3->GetComponent<RigidBody>()->UseGravity = false;
		ent3->GetComponent<RigidBody>()->mass = 10.8f;
		ent3->GetComponent<RigidBody>()->bounciness = 0.0f;

		ent3->transform->SetPosition(gm::vec3(50, 200, 0));
		
		ent2->transform->SetParent(ent1->transform);

		ent1->transform->SetPosition(gm::vec3(50, 50, 0));
		
		ent2->transform->SetPosition(gm::vec3(50, 50, 0));
		

	}

	virtual inline void OnUpdate() override
	{
	
		float dt = 128 * mae::Maestro::GetEngine()->deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			Maestro::GetEngine()->isRunning = false;
		}
		
		if (counter <= 3.5f)
		{
			counter += Maestro::GetEngine()->deltaTime;
		}
		else
		{
			ent1->GetComponent<RigidBody>()->UseGravity = true;
		}

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		{
			ent2->transform->Translate(gm::vec3::right() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
		{
			ent2->transform->Translate(gm::vec3::left() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		{
			ent2->transform->Translate(gm::vec3::down() * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		{
			ent2->transform->Translate(gm::vec3::up() * dt);
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
	sf::Texture brickTex;
	sf::SoundBuffer snd;

	mae::EntityHandle ent1;
	mae::EntityHandle ent2;	
	mae::EntityHandle ent3;
};
