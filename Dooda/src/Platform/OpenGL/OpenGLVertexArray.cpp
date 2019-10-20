#include "Ddpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Dooda
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Dooda::ShaderDataType::Float:    return GL_FLOAT;
		case Dooda::ShaderDataType::Float2:   return GL_FLOAT;
		case Dooda::ShaderDataType::Float3:   return GL_FLOAT;
		case Dooda::ShaderDataType::Float4:   return GL_FLOAT;
		case Dooda::ShaderDataType::Mat3:     return GL_FLOAT;
		case Dooda::ShaderDataType::Mat4:     return GL_FLOAT;
		case Dooda::ShaderDataType::Int:      return GL_INT;
		case Dooda::ShaderDataType::Int2:     return GL_INT;
		case Dooda::ShaderDataType::Int3:     return GL_INT;
		case Dooda::ShaderDataType::Int4:     return GL_INT;
		case Dooda::ShaderDataType::Bool:     return GL_BOOL;
		}

		DD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &d_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &d_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(d_rendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		DD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(d_rendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		d_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(d_rendererID);
		indexBuffer->Bind();

		d_indexBuffer = indexBuffer;
	}

}
