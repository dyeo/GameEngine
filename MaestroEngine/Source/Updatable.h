#ifndef _MAESTRO_UPDATABLE_H_
#define _MAESTRO_UPDATABLE_H_

#include "Maestro.h"

namespace MAESTRO_NAMESPACE
{
	class Updatable
	{
	public:

		virtual void OnCreate() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnFinish() = 0;
		virtual void OnDestroy() = 0;

	};
}

#endif // !_MAESTRO_UPDATABLE_H_