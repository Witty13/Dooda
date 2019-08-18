#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Dooda
{

	class DOODA_API Application
	{
	public: //Public Functions
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private: //Member Function
		bool OnWindowClose(WindowCloseEvent& e);

	private: //Private variables
		std::unique_ptr<Window> d_window;

		bool d_running = true;
	};

	Application* CreateApplication();

}