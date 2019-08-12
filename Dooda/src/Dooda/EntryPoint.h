#pragma once

#ifdef DD_PLATFORM_WINDOWS

extern Dooda::Application* Dooda::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Dooda::CreateApplication();
	app->Run();
	delete app;
}

#endif
