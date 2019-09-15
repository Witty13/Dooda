#include "Dooda.h"

#include "imgui/imgui.h"

class ExampleLayer : public Dooda::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), d_camera(-1.6f, 1.6f, -0.9f, 0.9f), d_cameraPosition(0.0f)
	{
		d_vertexArray.reset(Dooda::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Dooda::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Dooda::VertexBuffer::Create(vertices, sizeof(vertices)));
		Dooda::BufferLayout layout = {
			{ Dooda::ShaderDataType::Float3, "a_Position" },
			{ Dooda::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		d_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Dooda::IndexBuffer> indexBuffer;
		uint32_t indicies[3] = { 0, 1, 2 };
		indexBuffer.reset(Dooda::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		d_vertexArray->SetIndexBuffer(indexBuffer);

		d_squareVA.reset(Dooda::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Dooda::VertexBuffer> squareVB;
		squareVB.reset(Dooda::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Dooda::BufferLayout squareVBLayout = {
			{ Dooda::ShaderDataType::Float3, "a_Position" }
		};
		squareVB->SetLayout(squareVBLayout);
		d_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Dooda::IndexBuffer> squareIB;
		squareIB.reset(Dooda::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		d_squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		d_shader.reset(new Dooda::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		d_blueShader.reset(new Dooda::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	void OnUpdate(Dooda::Timestep ts) override
	{
		if (Dooda::Input::IsKeyPressed(DD_KEY_LEFT))
		{
			d_cameraPosition.x += d_cameraMoveSpeed * ts;
		}

		if (Dooda::Input::IsKeyPressed(DD_KEY_RIGHT))
		{
			d_cameraPosition.x -= d_cameraMoveSpeed * ts;
		}

		if (Dooda::Input::IsKeyPressed(DD_KEY_DOWN))
		{
			d_cameraPosition.y += d_cameraMoveSpeed * ts;
		}

		if (Dooda::Input::IsKeyPressed(DD_KEY_UP))
		{
			d_cameraPosition.y -= d_cameraMoveSpeed * ts;
		}

		if (Dooda::Input::IsKeyPressed(DD_KEY_A))
		{
			d_cameraRotation -= d_cameraRotationSpeed * ts;
		}

		if (Dooda::Input::IsKeyPressed(DD_KEY_D))
		{
			d_cameraRotation += d_cameraRotationSpeed * ts;
		}

		Dooda::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Dooda::RenderCommand::Clear();

		d_camera.SetPosition(d_cameraPosition);
		d_camera.SetRotation(d_cameraRotation);

		Dooda::Renderer::BeginScene(d_camera);

		Dooda::Renderer::Submit(d_blueShader, d_squareVA);
		Dooda::Renderer::Submit(d_shader, d_vertexArray);

		Dooda::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Dooda::Event& event) override
	{
	}

private:
	std::shared_ptr<Dooda::Shader> d_shader;
	std::shared_ptr<Dooda::VertexArray> d_vertexArray;

	std::shared_ptr<Dooda::Shader> d_blueShader;
	std::shared_ptr<Dooda::VertexArray> d_squareVA;

	Dooda::OrthographicCamera d_camera;
	glm::vec3 d_cameraPosition;
	float d_cameraRotation = 0.0f;
	float d_cameraRotationSpeed = 90.0f;
	float d_cameraMoveSpeed = 3.0f;

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