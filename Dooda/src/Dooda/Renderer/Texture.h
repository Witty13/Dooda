#pragma once

#include "Dooda/Core.h"

namespace Dooda {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(const std::string& name, uint32_t slot = 0) const = 0;
		virtual void AddTexture(const std::string& path, const std::string& name) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create();
	};

}