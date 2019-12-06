#include "Ddpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

#include "Renderer/Renderer.h"

namespace Dooda
{
	#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DD_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		d_window = std::unique_ptr<Window>(Window::Create());
		d_window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

		Renderer::Init();

		d_imGuiLayer = new ImGuiLayer();
		PushOverlay(d_imGuiLayer);

	}

	void Dooda::Application::Run()
	{
		while (d_running)
		{
			float time = (float)glfwGetTime(); //Platform::GetTime();
			Timestep timestep = time - d_lastFrameTime;
			d_lastFrameTime = time;

			for (Layer* layer : d_layerStack)
			{
				layer->OnUpdate(timestep);
			}

			d_imGuiLayer->Begin(); 
			for (Layer* layer : d_layerStack)
			{
				layer->OnImGuiRender();
			}
			d_imGuiLayer->End();

			d_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

		for (auto it = d_layerStack.end(); it != d_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		d_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		d_layerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		d_running = false;
		return true;
	}

}