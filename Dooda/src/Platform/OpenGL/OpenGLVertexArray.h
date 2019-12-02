#pragma once
#include "Dooda/Renderer/VertexArray.h"

namespace Dooda
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override{ return d_vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return d_indexBuffer; }

	private:
		uint32_t d_rendererID;
		std::vector<Ref<VertexBuffer>> d_vertexBuffers;
		Ref<IndexBuffer> d_indexBuffer; 
		uint32_t m_VertexBufferIndex = 0;
	};

}