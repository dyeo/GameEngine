#ifndef _MAESTRO_GAMEMODE_H_
#define _MAESTRO_GAMEMODE_H_

#include "Updatable.h"
#include "EntityHandle.h"

namespace mae
{
	class GameMode : Updatable
	{
		// methods
	public:

		GameMode();

		virtual void OnCreate() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnFixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnFinish() override;
		virtual void OnDestroy() override;

		/// <summary>
		/// Creates an Entity and adds it to the update loop.
		/// </summary>
		/// <returns>The Entity that was created.</returns>
		EntityHandle CreateEntity();

		/// <summary>
		/// Removes the Entity from the update loop and destroys it.
		/// </summary>
		/// <returns>True if the destroy operation was successful, false otherwise.</returns>
		bool DestroyEntity(EntityHandle ent);

		//members
	protected:
	};

}

#endif // !_MAESTRO_GAMEMODE_H_
