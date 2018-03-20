#ifndef _MAESTRO_MUSIC_H_
#define _MAESTRO_MUSIC_H_

#include "Component.h"

#include <SFML/Audio.hpp>

namespace mae
{

	class Music : public Component, public sf::Music
	{
		friend class Audio;

		// methods
	public:

		Music(System *const sys, EntityHandle ent);

		// members
	private:
	};

}

#endif // !_MAESTRO_MUSIC_H_
