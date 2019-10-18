#include "Dooda.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

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

		Dooda::Ref<Dooda::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Dooda::VertexBuffer::Create(vertices, sizeof(vertices)));
		Dooda::BufferLayout layout = {
			{ Dooda::ShaderDataType::Float3, "a_Position" },
			{ Dooda::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		d_vertexArray->AddVertexBuffer(vertexBuffer);

		Dooda::Ref<Dooda::IndexBuffer> indexBuffer;
		uint32_t indicies[3] = { 0, 1, 2 };
		indexBuffer.reset(Dooda::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		d_vertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Dooda::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Dooda::Ref<Dooda::VertexBuffer> squareVB;
		squareVB.reset(Dooda::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Dooda::BufferLayout squareVBLayout = {
			{ Dooda::ShaderDataType::Float3, "a_Position" },
			{ Dooda::ShaderDataType::Float2, "a_TexCoord" }
		};
		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		Dooda::Ref<Dooda::IndexBuffer> squareIB;
		squareIB.reset(Dooda::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		d_shader.reset(Dooda::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Dooda::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Dooda::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Dooda::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Dooda::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Dooda::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Dooda::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Dooda::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Dooda::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Dooda::Renderer::Submit(d_shader, d_vertexArray);

		m_Texture->Bind();
		Dooda::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Dooda::Renderer::Submit(m_Shader, m_VertexArray);
		Dooda::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Dooda::Event& event) override
	{
	}

private:
	Dooda::Ref<Dooda::Shader> d_shader;
	Dooda::Ref<Dooda::VertexArray> d_vertexArray;

	Dooda::Ref<Dooda::Shader> m_FlatColorShader, m_TextureShader;
	Dooda::Ref<Dooda::VertexArray> m_SquareVA;

	Dooda::Ref<Dooda::Texture2D> m_Texture;

	Dooda::OrthographicCamera d_camera;
	glm::vec3 d_cameraPosition;
	float d_cameraRotation = 0.0f;
	float d_cameraRotationSpeed = 90.0f;
	float d_cameraMoveSpeed = 3.0f;
	glm::vec3 m_SquareColor = glm::vec3( 0.2f, 0.3f, 0.8f );

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