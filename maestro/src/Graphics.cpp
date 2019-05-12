#include "Graphics.h"

#include "Transform.h"
#include "Sprite.h"
#include "Engine.h"

#include <algorithm>
#include <typeinfo>
#include <typeindex>

namespace mae
{

	Graphics::Graphics(Engine * const engine)
		: System(engine)
	{
		engine->SetManagingSystem<mae::Sprite>(this);
		sprites.reserve(65535);
	}

	Component * const Graphics::OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType)
	{
		if (cmpType == typeid(Sprite))
		{
			Sprite *spr = new Sprite(this, srcEnt);
			sprites.push_back(spr);
			return sprites.back();
		}
		return nullptr;
	}

	bool Graphics::OnComponentDestroy(EntityHandle srcEnt, Component *const srcCmp)
	{
		std::type_index cmpType = typeid(*srcCmp);
		if (cmpType == typeid(Sprite))
		{
			Sprite *const s = static_cast<Sprite*>(srcCmp);
			sprites.erase(std::remove(sprites.begin(), sprites.end(), s), sprites.end());
			delete s;
			return true;
		}
		return false;
	}

	void Graphics::OnUpdate()
	{
		for (int s = 0; s < sprites.size(); s++)
		{
			sprites[s]->OnUpdate();
		}
	}

	void Graphics::OnRender()
	{
		for (int s = 0; s < sprites.size(); s++)
		{
			sprites[s]->OnRender();
		}
	}

}
