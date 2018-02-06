#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Maestro.h"

namespace MAESTRO_NAMESPACE
{
	class System : public Updatable
	{
	public:
		
		template<typename CmpType> virtual CmpType* OnComponentCreate(Entity *srcEnt) = 0;
		template<typename CmpType> virtual bool OnComponentDestroy(Entity *srcEnt, CmpType *srcCmp) = 0;

	private:
	};
}

#endif // !_MAESTRO_SYSTEM_H_
