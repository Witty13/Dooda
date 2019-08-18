#include "Ddpch.h"
#include "Application.h"

namespace Dooda
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		d_window = std::unique_ptr<Window>(Window::Create());
		d_window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
	}

	Application::~Application()
	{
	}

	void Dooda::Application::Run()
	{
		while (d_running)
		{
			d_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

		DD_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		d_running = false;
		return true;
	}

}