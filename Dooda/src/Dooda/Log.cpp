#include "Log.h"

namespace Dooda
{

	std::shared_ptr<spdlog::logger> Log::d_coreLogger;
	std::shared_ptr<spdlog::logger> Log::d_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		d_coreLogger = spdlog::stdout_color_mt("Dooda");
		d_coreLogger->set_level(spdlog::level::trace);
		d_clientLogger = spdlog::stdout_color_mt("App");
		d_clientLogger->set_level(spdlog::level::trace);
	}

}
