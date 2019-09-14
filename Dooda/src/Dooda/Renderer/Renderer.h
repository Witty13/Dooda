#pragma once

#include "RenderCommand.h"

namespace Dooda
{

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetCurrentRendererAPI() { return RendererAPI::GetAPI(); }
	};

}