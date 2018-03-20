#ifndef _MAESTRO_SOUND_H_
#define _MAESTRO_SOUND_H_

#include "Component.h"

#include <SFML/Audio.hpp>

namespace mae
{

	class Sound : public Component, public sf::Sound
	{
		friend class Audio;

		// methods
	public:

		Sound(System *const sys, EntityHandle ent);

		// members
	private:
	};

}

#endif // !_MAESTRO_SOUND_H_
