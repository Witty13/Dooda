#include "Ddpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dooda {

	Ref<Texture2DManager> Texture2DManager::Create()
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:
		{
			DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLTexture2DManager>();
		}
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}