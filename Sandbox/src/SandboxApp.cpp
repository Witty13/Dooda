#include "Dooda.h"

#include "imgui/imgui.h"

class ExampleLayer : public Dooda::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//DD_CLIENT_INFO("Example Layer Udate");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Dooda::Event& event) override
	{
		//DD_CLIENT_TRACE("{0}", event);
	}
};

class SandBox : public Dooda::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

Dooda::Application* Dooda::CreateApplication()
{
	return new SandBox;
}