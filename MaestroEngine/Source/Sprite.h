#ifndef  _MAESTRO_SPRITE_H_
#define _MAESTRO_SPRITE_H_

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace mae
{

	// Component wrapper for an SFML sprite. 
	class Sprite : public Component, public sf::Sprite
	{
		friend class Graphics;
		
		// methods
	public:

		Sprite(System * const sys, EntityHandle ent);

		virtual void OnUpdate() override;

		virtual void OnRender() override;

		// members
	private:
	};

}

#endif // ! _MAESTRO_SPRITE_H_
