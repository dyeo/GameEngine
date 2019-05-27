#include <stdio.h>
#include <Engine.h>
#include <Maestro.h>
#include <SceneGraph.h>

#include <iostream>

using namespace mae;

class TestMode : public GameMode
{
public:

	TestMode() {}

	virtual void OnStart() override
	{
		auto a = CreateEntity();
		auto t = a->GetComponent<Transform>();

		LOG_MESSAGE("Hello world!");
	}
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