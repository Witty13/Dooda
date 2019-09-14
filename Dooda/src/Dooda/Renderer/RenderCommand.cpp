#include "Ddpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dooda {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}