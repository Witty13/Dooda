#pragma once

#include "Dooda.h"

#ifdef DD_PLATFORM_WINDOWS

extern Dooda::Application* Dooda::CreateApplication();

int main(int argc, char** argv)
{
	Dooda::Log::Init();
	("Init worked");
	DD_CLIENT_INFO("Yolo");

	auto app = Dooda::CreateApplication();
	app->Run();
	delete app;
}

#endif
