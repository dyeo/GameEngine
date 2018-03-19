#ifndef  _MAESTRO_SPRITE_H_
#define _MAESTRO_SPRITE_H_

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace mae
{

	// Component wrapper for an SFML sprite. 
	class Sprite : public Component
	{
		friend class Graphics;
		
		// methods
	public:

		Sprite(System * const sys, EntityHandle ent);

		sf::Sprite sprite;

		// members
	private:
	};

}

#endif // ! _MAESTRO_SPRITE_H_
