#pragma once

#include "Application.h"

#ifdef DD_PLATFORM_WINDOWS

extern Dooda::Application* Dooda::CreateApplication();

int main(int argc, char** argv)
{
	Dooda::Log::Init();

	auto app = Dooda::CreateApplication();
	app->Run();
	delete app;
}

#endif
