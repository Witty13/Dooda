#pragma once

#include "Dooda/Renderer/Texture.h"

namespace Dooda {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D();
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(const std::string& name, uint32_t slot = 0) const override;
		virtual void AddTexture(const std::string& path, const std::string& name) override;
	private:
		uint32_t m_Width, m_Height;
		std::unordered_map<std::string, uint32_t> m_RendererIDs;
		uint32_t m_RendererID;
	};

}