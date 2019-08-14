#pragma once

#include "Core.h"

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Dooda
{

	class DOODA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return d_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return d_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> d_coreLogger;
		static std::shared_ptr<spdlog::logger> d_clientLogger;
	};
}

//Core log macros
#define DD_CORE_TRACE(...)	::Dooda::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DD_CORE_INFO(...)	::Dooda::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DD_CORE_WARN(...)	::Dooda::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DD_CORE_ERROR(...)	::Dooda::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DD_CORE_FATAL(...)	::Dooda::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Core log macros
#define DD_Client_TRACE(...)	::Dooda::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DD_Client_INFO(...)		::Dooda::Log::GetClientLogger()->info(__VA_ARGS__)
#define DD_Client_WARN(...)		::Dooda::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DD_Client_ERROR(...)	::Dooda::Log::GetClientLogger()->error(__VA_ARGS__)
#define DD_Client_FATAL(...)	::Dooda::Log::GetClientLogger()->fatal(__VA_ARGS__)