#include "Ddpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dooda {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetCurrentRendererAPI())
			{
			case RendererAPI::None:
			{
				DD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGl:
			{
				return new OpenGLVertexArray();
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

}
