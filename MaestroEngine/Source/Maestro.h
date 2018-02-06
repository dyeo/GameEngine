#ifndef _MAESTRO_MAESTRO_H_
#define _MAESTRO_MAESTRO_H_

#define MAESTRO_NAMESPACE mst

#include "Composable.h"
#include "Updatable.h"
#include "System.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"

#include <vector>
#include <utility>
#include <typeindex>

namespace MAESTRO_NAMESPACE
{
	class Maestro : public Updatable
	{
	public:

		void Run();

		template<typename S> bool AddSystem();
		template<typename S> bool RemoveSystem();
		template<typename S> System *GetSystem();

		template<typename SysType> static std::type_index GetSystemIndex();

		virtual void OnCreate() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;
		virtual void OnFinish() override;
		virtual void OnDestroy() override;

	private:

		std::vector<std::pair<std::type_index, System>> systems;
	};
}

#endif // !_MAESTRO_MAESTRO_H_