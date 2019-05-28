#ifndef _MAESTRO_REF_H_
#define _MAESTRO_REF_H_

#include <cstdint>

namespace mae
{
	//! A handle reference to a managed entity or component within the engine.
	template <typename T>
	class ref
	{
	public:

		ref() : index(0), counter(0)
		{}

		ref(uint32_t index, uint32_t counter)
			: index(index), counter(counter)
		{}

		inline operator uint32_t() const
		{
			return counter << 24 | index;
		}

	private:

		uint32_t index : 24;
		uint32_t counter : 8;
	};
}

#endif //! _MAESTRO_REF_H_