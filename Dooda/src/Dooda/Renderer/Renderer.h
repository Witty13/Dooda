#pragma once

namespace Dooda
{

	enum class RendererAPI
	{
		None = 0,
		OpenGl = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetCurrentRendererAPI() { return D_rendererAPI; }

	private:
		static RendererAPI D_rendererAPI;
	};

}