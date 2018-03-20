#include "Audio.h"

#include "Engine.h"
#include "Sound.h"
#include "Music.h"

#include <typeinfo>
#include <typeindex>

namespace mae
{
	Audio::Audio(Engine *const engine)
		:System(engine)
	{
		engine->SetManagingSystem<Sound>(this);
		engine->SetManagingSystem<Music>(this);
	}

	Component * const Audio::OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType)
	{
		if (cmpType == std::type_index(typeid(Sound)))
		{
			Sound *snd = new Sound(this, srcEnt);
			sounds.push_back(snd);
			return sounds.back();
		}
		else if (cmpType == std::type_index(typeid(Music)))
		{
			Music *mus = new Music(this, srcEnt);
			music.push_back(mus);
			return music.back();
		}
		return nullptr;
	}

	bool Audio::OnComponentDestroy(EntityHandle srcEnt, Component *const srcCmp)
	{
		auto cmpType = std::type_index(typeid(*srcCmp));
		if (cmpType == std::type_index(typeid(Sound)))
		{
			Sound *const s = static_cast<Sound*>(srcCmp);
			sounds.erase(std::remove(sounds.begin(), sounds.end(), s), sounds.end());
			delete s;
			return true;
		}
		else if (cmpType == std::type_index(typeid(Music)))
		{
			Music *const m = static_cast<Music*>(srcCmp);
			music.erase(std::remove(music.begin(), music.end(), m), music.end());
			delete m;
			return true;
		}
		return false;
	}
}