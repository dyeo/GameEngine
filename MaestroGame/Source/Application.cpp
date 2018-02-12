#include "Maestro.h"

#include "Engine.h"

int main(char *argc, char **argv)
{
	using namespace mae;
	Maestro::Initialize();
	Maestro::GetEngine()->Run();
	Maestro::Destroy();
}