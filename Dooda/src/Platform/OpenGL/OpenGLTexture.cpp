#include "Ddpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Dooda {

	OpenGLTexture2D::OpenGLTexture2D()
		: m_RendererIDs()
	{
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(const std::string& name, uint32_t slot) const
	{
		std::unordered_map<std::string, uint32_t>::const_iterator got = m_RendererIDs.find(name);
		if (got == m_RendererIDs.end())
		{
			return;
		}

		glBindTexture(GL_TEXTURE_2D, got->second);
	}
	void OpenGLTexture2D::AddTexture(const std::string& path, const std::string& name)
	{

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		DD_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB;
			dataFormat = GL_RGBA;

		}

		DD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		uint32_t rendererID;
		glGenTextures(1, &rendererID);

		//Generate the texture
		glActiveTexture(GL_TEXTURE0);
		m_RendererIDs.emplace(name, rendererID);

		glBindTexture(GL_TEXTURE_2D, rendererID);



/*Error Checking
#if glCreateTextures != NULL

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

#endif
*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
}