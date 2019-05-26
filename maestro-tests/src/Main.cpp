#include <stdio.h>
#include <Engine.h>
#include <Maestro.h>
#include <SceneGraph.h>

using namespace mae;

class TestMode : public GameMode
{
public:

	TestMode() {}
};

int main(int argc, char **argv)
{
	Maestro::Initialize();
	auto engine = Maestro::GetEngine();

	engine->AddSystem<SceneGraph>();
	engine->gameModeStack.push(new TestMode());

	engine->Run();

	return 0;
}