#ifndef _MAESTRO_SCENEGRAPH_H_
#define _MAESTRO_SCENEGRAPH_H_

#include "System.h"

#include "Transform.h"

namespace mae
{

	class SceneGraph : public System
	{
		// methods
	public:

		SceneGraph(Engine *const engine);

		virtual Component *const OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType) override;
		
		virtual bool OnComponentDestroy(EntityHandle srcEnt, Component * const srcCmp) override;

		virtual void OnUpdate() override;

	private:

		bool DestroyTransform(Transform *const current, Transform *const target);

		// members
	private:

		std::vector<Transform*> roots;

	};

}

#endif //!_MAESTRO_SCENEGRAPH_H_