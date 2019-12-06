#pragma once

#include "Dooda/Renderer/Texture.h"

namespace Dooda {

	struct TextureInfo
	{
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};

	class OpenGLTexture2DManager : public Texture2DManager
	{
	public:
		OpenGLTexture2DManager();
		virtual ~OpenGLTexture2DManager();

		virtual uint32_t GetWidth(const std::string& name) const override { return m_TextureInfo.find(name)->second.m_Width; }
		virtual uint32_t GetHeight(const std::string& name) const override { return m_TextureInfo.find(name)->second.m_Height; }

		virtual void Bind(const std::string& name, uint32_t slot = 0) const override;
		virtual void AddTexture(const std::string& path, const std::string& name) override;

	private:
		std::unordered_map<std::string, TextureInfo> m_TextureInfo;
	};

}