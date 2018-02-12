#ifndef _MAESTRO_COMPONENT_HANDLE_HPP_
#define _MAESTRO_COMPONENT_HANDLE_HPP_

#include "Maestro.h"

#include <cstdint>
#include <type_traits>

namespace mae
{

	template <typename C>
	class ComponentHandle
	{
		// methods
	public:
		
		/// <summary>
		/// Constructs a ComponentHandle instance from an existing Component.
		/// </summary>
		/// <param name="srcComp">The source Component.</param>
		ComponentHandle(C *const srcComp);
		
		/// <summary>
		/// Retrieves the Component referenced by this ComponentHandle.
		/// </summary>
		/// <returns>The referenced Component if one exists, or nullptr otherwise.</returns>
		C *const operator->();
		
		/// <summary>
		/// Determines if a Component referenced by a ComponentHandle is equal to another.
		/// </summary>
		/// <param name="other">The other ComponentHandle.</param>
		/// <returns></returns>
		bool operator==(const ComponentHandle &other);

	private:

		ComponentHandle();

		// members
	private:

		uint32_t uniqueId;
		uint32_t handleIndex;

	};

	template<typename C>
	inline ComponentHandle<C>::ComponentHandle(C * const srcComp)
		: ComponentHandle()
	{
		uniqueId = srcComp->uniqueId;
		handleIndex = srcComp->handleIndex;
	}

	template<typename C>
	inline C * const ComponentHandle<C>::operator->()
	{
		return Maestro::GetEngine()->GetManagingSystem<C>()->handles[handleIndex];
	}

	template<typename C>
	inline bool ComponentHandle<C>::operator==(const ComponentHandle & other)
	{
		return uniqueId == other.uniqueId && handleIndex == other.handleIndex;
	}

	template<typename C>
	inline ComponentHandle<C>::ComponentHandle()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
	}

}

#endif // !_MAESTRO_COMPONENT_HANDLE_HPP_
