#pragma once

#ifdef DD_PLATFORM_WINDOWS
	#ifdef DD_BUILD_DLL
		#define DOODA_API __declspec(dllexport)
	#else 
		#define DOODA_API __declspec(dllimport)
	#endif
#else
	#error Dooda only suports windows
#endif

#define BIT(x) (1 << x)