#include "Maestro.h"

#include "Engine.h"
#include "SceneGraph.h"
#include "TestGameMode.hpp"

int main(char *argc, char **argv)
{
	using namespace mae;
	Maestro::Initialize();
	Maestro::GetEngine()->AddSystem<SceneGraph>();
	Maestro::GetEngine()->AddSystem<PhysicsEngine>();
	Maestro::GetEngine()->gameModeStack.push(new TestGameMode());
	Maestro::GetEngine()->Run();
	Maestro::Destroy();
}