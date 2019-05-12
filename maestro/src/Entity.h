#ifndef _MAESTRO_ENTITY_H_
#define _MAESTRO_ENTITY_H_

#include <map>
#include <typeindex>

namespace mae
{
	class Transform;

	/// <summary>
	/// A static Component that contains other components, and is the smallest object representable in a game Scene.
	/// </summary>
	class Entity
	{
		friend class Component;
		friend class EntityHandle;
		friend class ObjectFactory;

		// methods
	public:

		bool operator==(const Entity &other);

		/// <summary>
		/// Gets the first Component of this type from this Component's Entity.
		/// </summary>
		/// <returns>The Component if it exists, or nullptr otherwise.</returns>
		template <typename C> C *const GetComponent();
		Component *const GetComponent(std::type_index cmpType);

		/// <summary>
		/// Gets the first Component of this type from this Component's Entity.
		/// </summary>
		/// <param name="mpInd">The order of the Components of the current type, ranging from 0-n, where 0 is the first created Component and n is the last.</param>
		/// <returns>The Component if it exists, or nullptr otherwise.</returns>
		template <typename C> C *const GetComponent(int cmpInd);
		Component *const GetComponent(int cmpInd, std::type_index cmpType);

		/// <summary>
		/// Creates a Component and assigns it to its respective System to be updated by the Engine.
		/// </summary>
		/// <returns>The created Component, or nullptr if the Component could not be created.</returns>
		template <typename C> C *const AddComponent();
		Component *const AddComponent(std::type_index cmpType);

		/// <summary>
		/// Removes a Component from its respective Saystem and destroys it.
		/// </summary>
		/// <param name="component">The component to be destroyed.</param>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		template <typename C> bool RemoveComponent(C *const cmp);
		bool RemoveComponent(Component *const cmp, std::type_index cmpType);
		
	private:

		Entity();
		
		// members
	public:

		const char *name = "New Entity";	

		Transform * transform;

		std::multimap<std::type_index, Component *const> components;

		uint32_t handleIndex;
		uint32_t handleUid;

	private:
	};

	template <typename C> C *const Entity::GetComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return static_cast<C *const>(GetComponent(cmpType));
	}

	template <typename C> C *const Entity::GetComponent(int cmpInd)
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return static_cast<C *const>(GetComponent(cmpInd, cmpType));
	}

	template <typename C> inline C *const Entity::AddComponent()
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return static_cast<C *const>(AddComponent(cmpType));
	}

	template <typename C> inline bool Entity::RemoveComponent(C *const component)
	{
		static_assert(std::is_base_of<Component, C>::value, "Generic C does not inherit Component.");
		std::type_index cmpType = std::type_index(typeid(C));

		return RemoveComponent(static_cast<Component *const>(component), cmpType);
	}

}

#endif // !_MAESTRO_ENTITY_H_
