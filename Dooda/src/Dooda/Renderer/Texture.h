#pragma once

#include "Dooda/Core.h"

namespace Dooda {

	class TextureManager
	{
	public:
		virtual ~TextureManager() = default;

		virtual uint32_t GetWidth(const std::string& name) const = 0;
		virtual uint32_t GetHeight(const std::string& name) const = 0;

		virtual void Bind(const std::string& name, uint32_t slot = 0) const = 0;
		virtual void AddTexture(const std::string& path, const std::string& name) = 0;
	};

	class Texture2DManager : public TextureManager
	{
	public:
		static Ref<Texture2DManager> Create();
	};

}