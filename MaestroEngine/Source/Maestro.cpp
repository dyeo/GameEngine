#include "Maestro.h"

#include "Engine.h"

namespace mae
{
	Engine * Maestro::engine = nullptr;

	void Maestro::Initialize()
	{
		if (engine == nullptr)
		{
			engine = new Engine();
		}
	}

	void Maestro::Destroy()
	{
		delete engine;
		engine = nullptr;
	}

	Engine * const Maestro::GetEngine()
	{
		return engine;
	}

}