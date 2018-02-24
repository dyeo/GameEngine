#include "Maestro.h"

#include "Engine.h"
#include "SceneGraph.h"

int main(char *argc, char **argv)
{
	using namespace mae;
	Maestro::Initialize();
	Maestro::GetEngine()->AddSystem<SceneGraph>();
	Maestro::GetEngine()->Run();
	Maestro::Destroy();
}