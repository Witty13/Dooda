#pragma once

#include "Dooda/Renderer/Buffer.h"

namespace Dooda 
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual const BufferLayout& GetLayout() const override { return d_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { d_Layout = layout; }
		
	private:
		uint32_t d_rendererID;
		BufferLayout d_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual uint32_t GetCount() const { return d_count; }

	private:
		uint32_t d_rendererID;
		uint32_t d_count;
	};
}