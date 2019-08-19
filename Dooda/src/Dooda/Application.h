#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private: //Member Function
		bool OnWindowClose(WindowCloseEvent& e);

	private: //Private variables
		std::unique_ptr<Window> d_window;

		bool d_running = true;

		LayerStack d_layerStack;
	};

	Application* CreateApplication();

}