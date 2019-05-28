#ifndef _MAESTRO_MANAGER_H_
#define _MAESTRO_MANAGER_H_

#include <vector>
#include <cstdint>

namespace mae
{
	//! A standard manager which creates, destroys, and manages entities or components, and provides user-accessible references.
	template <typename T>
	class manager
	{
		template<typename U> friend class ref;

	public:

		manager()
		{
			data.reserve(16777215);
		}

		ref<T> create()
		{
		}

		bool destroy(ref<T> v)
		{
		}

	private:

	};
}

#endif