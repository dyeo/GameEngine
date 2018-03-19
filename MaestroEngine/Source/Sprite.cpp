#include "Sprite.h"

#include "Maestro.h"
#include "Engine.h"
#include "Logging.h"
#include "Transform.h"

#include <SFML/Graphics.hpp>

namespace mae
{

	Sprite::Sprite(System * const sys, EntityHandle ent)
		: Component(sys, ent)
	{		
	}

	void Sprite::OnUpdate()
	{
		setPosition(entity->transform->GetPosition().x, entity->transform->GetPosition().y);
		printf("Sprite::OnUpdate");
	}

	void Sprite::OnRender()
	{
		Maestro::GetEngine()->window.draw(*this);
		printf("Sprite::OnRender");
	}

}
