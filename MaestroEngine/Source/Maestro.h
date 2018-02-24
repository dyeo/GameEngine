#ifndef _MAESTRO_MAESTRO_H_
#define _MAESTRO_MAESTRO_H_

#include "Logging.h"

namespace mae
{	
	class Engine;

	/// <summary>
	/// Static class responsible for safe and simple user interface with the engine.
	/// </summary>
	class Maestro
	{
		// methods
	public:

		static void Initialize();
		static void Destroy();
		static Engine *const GetEngine();

		// members
	private:

		static Engine *engine;

	};
}

#endif // !_MAESTRO_MAESTRO_H_
