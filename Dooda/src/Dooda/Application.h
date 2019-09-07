#pragma once

#include "Core.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

#include "Dooda/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *d_window; }

	private: //Member Function
		bool OnWindowClose(WindowCloseEvent& e);

	private: //Private variables
		std::unique_ptr<Window> d_window;

		ImGuiLayer* d_imGuiLayer;

		bool d_running = true;

		LayerStack d_layerStack;

		unsigned int d_vertexArray;
		std::unique_ptr<Shader> d_shader;
		std::unique_ptr<VertexBuffer> d_vertexBuffer;
		std::unique_ptr<IndexBuffer> d_indexBuffer;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}