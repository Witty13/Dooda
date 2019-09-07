#include "Ddpch.h"
#include "Application.h"

#include "glad/glad.h"

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

		d_imGuiLayer = new ImGuiLayer();
		PushOverlay(d_imGuiLayer);

		glGenVertexArrays(1, &d_vertexArray);
		glBindVertexArray(d_vertexArray);

		float verticies[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		d_vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indicies[3] = { 0, 1, 2 };
		d_indexBuffer.reset(IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		d_shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Dooda::Application::Run()
	{
		while (d_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			d_shader->Bind();
			glBindVertexArray(d_vertexArray);
			glDrawElements(GL_TRIANGLES, d_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : d_layerStack)
			{
				layer->OnUpdate();
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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		d_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		d_running = false;
		return true;
	}

}