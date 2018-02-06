#ifndef _MAESTRO_COMPOSABLE_H_
#define _MAESTRO_COMPOSABLE_H_

#include "Maestro.h"

namespace MAESTRO_NAMESPACE
{
	class Composable
	{
	public:

		virtual void CreateComponent() = 0;
		virtual void DestroyComponent() = 0;
		virtual void CreateEntity() = 0;
		virtual void DestroyEntity() = 0;

	};
}

#endif // !_MAESTRO_COMPOSABLE_H_