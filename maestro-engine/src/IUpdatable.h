#ifndef _MAESTRO_UPDATABLE_H_
#define _MAESTRO_UPDATABLE_H_

namespace mae
{
	
	/// <summary>
	/// The IUpdatable interface contract enforces objects that inherit from this interface are capable of being part of the Engine update loop.
	/// </summary>
	class IUpdatable
	{
		// methods
	public:

		virtual ~IUpdatable() {};

		/// <summary>
		/// Called once when the IUpdatable is created, before OnStart or OnUpdate.
		/// </summary>
		virtual void OnCreate() = 0;

		/// <summary>
		/// Called once during the update loop for this IUpdatable, before the first OnUpdate.
		/// </summary>
		virtual void OnStart() = 0;

		/// <summary>
		/// Called during the update loop for this IUpdatable, and is called at least once per frame.
		/// </summary>
		virtual void OnUpdate() = 0;

		/// <summary>
		/// Called once per physics frame for this Updatadable.
		/// </summary>
		virtual void OnFixedUpdate() = 0;

		/// <summary>
		/// Called following OnUpdate for this IUpdatable, and is called as many times as possible per frame (or once per frame if vsync is enabled).
		/// </summary>
		virtual void OnRender() = 0;

		/// <summary>
		/// Called once after the update loop for this IUpdatable, before any Updatables in this object's update loop are destroyed.
		/// </summary>
		virtual void OnFinish() = 0;

		/// <summary>
		/// Called after OnFinish for this IUpdatable, before the object is destroyed.
		/// </summary>
		virtual void OnDestroy() = 0;

		// members
	private:
	};

}

#endif // !_MAESTRO_UPDATABLE_H_