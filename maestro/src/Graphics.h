#ifndef _MAESTRO_GRAPHICS_H_
#define _MAESTRO_GRAPHICS_H_

#include "System.h"

#include <vector>

namespace mae
{
	class Engine;

	class Graphics : public System
	{
		friend class Sprite;

		// methods
	public:

		Graphics(Engine *const engine);

		virtual Component * const OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType) override;

		virtual bool OnComponentDestroy(EntityHandle srcEnt, Component * const srcCmp) override;
		
		virtual void OnUpdate() override;

		virtual void OnRender() override;

		// members
	private:

		std::vector<Sprite*> sprites;

	};

}

#endif // !_MAESTRO_GRAPHICS_H_
