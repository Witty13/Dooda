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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override{ return d_vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return d_indexBuffer; }

	private:
		uint32_t d_rendererID;
		std::vector< std::shared_ptr<VertexBuffer>> d_vertexBuffers;
		std::shared_ptr<IndexBuffer> d_indexBuffer;
	};

}