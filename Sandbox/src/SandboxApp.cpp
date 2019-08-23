#include <Dooda.h>

class ExampleLayer : public Dooda::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		DD_CLIENT_INFO("Example Layer Udate");
	}

	void OnEvent(Dooda::Event& event) override
	{
		DD_CLIENT_TRACE("{0}", event);
	}
};

class SandBox : public Dooda::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Dooda::ImGuiLayer());
	}

	~SandBox()
	{

	}
};

Dooda::Application* Dooda::CreateApplication()
{
	return new SandBox;
}