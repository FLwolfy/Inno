#pragma once

// ---------------Platforms--------------- //
#ifdef INNO_PLATFORM_WINDOWS
	// Windows API
#elif INNO_PLATFORM_LINUX
	// Linux API
#elif INNO_PLATFORM_MACOS
	// Mac API
#else
	// Inno Not Supported
#endif

// ---------------Core Consts--------------- //
#ifdef INNO_DEBUG
	#include "Inno/Core/Log.h"
	#define INNO_ASSERT(x, ...) { if (!x) { INNO_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define INNO_CORE_ASSERT(x, ...) { if (!x) { INNO_CORE_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define INNO_ASSERT(x, ...) // Strip it
	#define INNO_CORE_ASSERT(x, ...) // Strip it
#endif

