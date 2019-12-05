#include "Ddpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Dooda
{
	/////////////////
	//Vertex Buffer//
	/////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
	{
		glGenBuffers(1, &d_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, d_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &d_rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, d_rendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////
	//Index Buffer//
	////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
		:
		d_count(count)
	{
		glGenBuffers(1, &d_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, d_rendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &d_rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_rendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
