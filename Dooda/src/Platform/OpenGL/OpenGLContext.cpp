#include "Ddpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

Dooda::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: d_windowHandle(windowHandle)
{
	DD_CORE_ASSERT(d_windowHandle, "Window handle is null")
}

Dooda::OpenGLContext::~OpenGLContext()
{
}

void Dooda::OpenGLContext::Init()
{
	glfwMakeContextCurrent(d_windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	DD_CORE_ASSERT(status, "Failed to load Glad");

	DD_CORE_INFO("OpenGL Info");
	DD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	DD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	DD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void Dooda::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(d_windowHandle);
}
