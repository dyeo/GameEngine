#ifndef _MAESTRO_COMPONENT_HANDLE_HPP_
#define _MAESTRO_COMPONENT_HANDLE_HPP_

#include "Maestro.h"

#include <cstdint>
#include <type_traits>
#include <typeindex>

namespace mae
{
	class Component;

	/// <summary>
	/// Stores a safe reference to a Component or Entity.
	/// </summary>
	class Handle
	{
		// methods
	public:
		
		/// <summary>
		/// Constructs a Handle instance from an existing Component.
		/// </summary>
		/// <param name="srcComp">The source Component.</param>
		Handle(Component *const srcComp);
		
		/// <summary>
		/// Retrieves the Component referenced by this Handle.
		/// </summary>
		/// <returns>The referenced Component if one exists, or nullptr otherwise.</returns>
		Component *const operator->();

		/// <summary>
		/// Dereferences the handle.
		/// </summary>
		/// <returns>The referenced Component if one exists, or nullptr otherwise.</returns>
		Component *const operator*();
		
		/// <summary>
		/// Determines if a Component referenced by a Handle is equal to another.
		/// </summary>
		/// <param name="other">The other Handle.</param>
		/// <returns></returns>
		bool operator==(const Handle &other);

		/// <summary>
		/// The Component's type.
		/// </summary>
		const std::type_index Type;

	private:

		Handle();

		// members
	private:

		uint32_t uniqueId;
		uint32_t handleIndex;

	};

}

#endif // !_MAESTRO_COMPONENT_HANDLE_HPP_
