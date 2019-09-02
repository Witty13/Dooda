#pragma once

#ifdef DD_PLATFORM_WINDOWS
	#ifdef DD_DYNAMIC_LINK
		#ifdef DD_BUILD_DLL
			#define DOODA_API __declspec(dllexport)
		#else 
			#define DOODA_API __declspec(dllimport)
		#endif
	#else
		#define DOODA_API
	#endif
#else
	#error Dooda only suports windows
#endif

#ifdef DD_DEBUG
	#define DD_ENABLE_ASSERTS
#endif

#ifdef DD_ENABLE_ASSERTS
	#define DD_ASSERT(x, ...) { if(!(x)) { DD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DD_CORE_ASSERT(x, ...) { if(!(x)) { DD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define DD_ASSERT(x, ...)
	#define DD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define DD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)