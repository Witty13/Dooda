#include "Ddpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Dooda
{

	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
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
				return new OpenGLVertexBuffer(verticies, size);
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t size)
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
				return new OpenGLIndexBuffer(indicies, size);
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

}
