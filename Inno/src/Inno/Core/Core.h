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

// ---------------Macros Const Defines--------------- //
#ifdef INNO_DEBUG
	#include "Inno/Core/Log.h"

    /// <summary>
    /// Asserts the given condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
    /// </summary>
    /// <param name="x">: The condition to be asserted.</param>
    /// <param name="...">: The error message format.</param>
    #define INNO_ASSERT(x, ...) { if (!(x)) { INNO_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

    /// <summary>
    /// Asserts the given core condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
    /// </summary>
    /// <param name="x">: The condition to be asserted.</param>
    /// <param name="...">: The error message format.</param>
    #define INNO_CORE_ASSERT(x, ...) { if (!(x)) { INNO_CORE_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
    /// <summary>
    /// Asserts the given condition in release mode. In release mode, this macro does nothing.
    /// </summary>
    /// <param name="x">: The condition to be asserted.</param>
    /// <param name="...">: The error message format (unused in release mode).</param>
    #define INNO_ASSERT(x, ...)

    /// <summary>
    /// Asserts the given core condition in release mode. In release mode, this macro does nothing.
    /// </summary>
    /// <param name="x">: The condition to be asserted.</param>
    /// <param name="...">: The error message format (unused in release mode).</param>
    #define INNO_CORE_ASSERT(x, ...)
#endif

/// <summary>
/// Binds a member function to a specific instance for use with std::function or similar constructs.
/// </summary>
/// <param name="func">: The member function to be bound.</param>
/// <param name="instance">: The instance of the class on which the member function will be called.</param>
/// <returns>A std::function object that can be called with the specified function and instance.</returns>
#define BIND_FUNC(func, instance) std::bind(&func, instance, std::placeholders::_1)

