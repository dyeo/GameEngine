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
		Transform *const t = entity->transform;
		setPosition(t->GetPosition().x, t->GetPosition().y);
		setScale(t->GetScale().x, t->GetScale().y);
	}

	void Sprite::OnRender()
	{
		Maestro::GetEngine()->window.draw(*this);
	}

}
