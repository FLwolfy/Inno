#pragma once

// ---------------Platforms--------------- //
#ifdef INNO_PLATFORM_WINDOWS
	#ifdef INNO_BUILD_DLL
		#define INNO_API __declspec(dllexport)
	#else
		#define INNO_API __declspec(dllimport)
	#endif
#else
	// Inno now only supports Windows!
#endif

// ---------------Core Consts--------------- //