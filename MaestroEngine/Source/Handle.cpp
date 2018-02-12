#include "Handle.h"

#include "Component.h"

namespace mae
{

	Handle::Handle(Component *const srcComp)
		: Type(typeid(*srcComp))
		, uniqueId(srcComp->uniqueId)
		, handleIndex(srcComp->handleIndex)
	{
	}

	inline Component *const Handle::operator->()
	{
		return Maestro::GetEngine()->GetManagingSystem(Type)->handles[handleIndex];
	}

	Component *const Handle::operator*()
	{
		return Maestro::GetEngine()->GetManagingSystem(Type)->handles[handleIndex];
	}

	inline bool Handle::operator==(const Handle & other)
	{
		return uniqueId == other.uniqueId && handleIndex == other.handleIndex;
	}

}