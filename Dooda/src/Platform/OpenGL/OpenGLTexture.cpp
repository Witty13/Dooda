#include "Ddpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Dooda {

	OpenGLTexture2DManager::OpenGLTexture2DManager()
	{
	}

	OpenGLTexture2DManager::~OpenGLTexture2DManager()
	{
		for (auto i = m_TextureInfo.begin(); i != m_TextureInfo.end(); i++) 
		{
			glDeleteTextures(1, &i->second.m_RendererID);
		}
	}

	void OpenGLTexture2DManager::Bind(const std::string& name, uint32_t slot) const
	{
		auto Find = m_TextureInfo.find(name);
		if (Find != m_TextureInfo.end())
		{
			glBindTexture(GL_TEXTURE_2D, Find->second.m_RendererID);
		}
	}
	void OpenGLTexture2DManager::AddTexture(const std::string& path, const std::string& name)
	{
		//Variables
		int width, height, channels;
		TextureInfo TempTexture;
		GLenum internalFormat = 0, dataFormat = 0;

		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		DD_CORE_ASSERT(data, "Failed to load image!");

		TempTexture.m_Width = width;
		TempTexture.m_Height = height;

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

		//Generate the texture
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &TempTexture.m_RendererID);
		glBindTexture(GL_TEXTURE_2D, TempTexture.m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, TempTexture.m_Width, TempTexture.m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TempTexture.m_Width, TempTexture.m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
		m_TextureInfo.emplace(name, TempTexture);
	}
}