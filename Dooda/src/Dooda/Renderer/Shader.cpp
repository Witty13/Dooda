#include "Ddpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dooda
{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:    
		{
			DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr; 
		}
		case RendererAPI::API::OpenGL: {
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		}
		
		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
