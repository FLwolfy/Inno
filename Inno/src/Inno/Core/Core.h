#pragma once

#include "Inno/Core/Log.h"

// ---------------------------------------------- //
// ---------------Platform Defines--------------- //
// ---------------------------------------------- //
#ifdef _WIN32
    #ifdef _WIN64
        /* Windows x64  */
        #define INNO_PLATFORM_WINDOWS 1
    #else
        /* Windows x86 */
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all the platforms
     * so we must check all of them (in this order)
     * to ensure that we're running on MAC
     * and not some other Apple platform */

    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #error "iOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #ifdef __arm64__
            #define INNO_PLATFORM_MACOSX 1
        #else
            #error "Unsupported macOS architecture!"
        #endif
    #else
        #error "Unknown Apple platform!"
    #endif
#else
    #error "Unsupported platform!"
#endif

// -------------------------------------------------- //
// ---------------Macros Const Defines--------------- //
// -------------------------------------------------- //


// --------------- Assertions --------------- //
#ifdef INNO_DEBUG
    #ifdef INNO_PLATFORM_WINDOWS
        /**
         * @brief Asserts the given condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
         * @param x The condition to be asserted.
         * @param ... The error message format.
         */
        #define INNO_ASSERT(x, ...) { if (!(x)) { INNO_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

        /**
         * @brief Asserts the given core condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
         * @param x The condition to be asserted.
         * @param ... The error message format.
         */
        #define INNO_CORE_ASSERT(x, ...) { if (!(x)) { INNO_CORE_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

    #elif INNO_PLATFORM_MACOSX
        /**
         * @brief Asserts the given condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
         * @param x The condition to be asserted.
         * @param ... The error message format.
         */
        #define INNO_ASSERT(x, ...) { if (!(x)) { INNO_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_debugtrap();}}

        /**
         * @brief Asserts the given core condition in debug mode. If the condition is false, logs an error message and triggers a debug break.
         * @param x The condition to be asserted.
         * @param ... The error message format.
         */
        #define INNO_CORE_ASSERT(x, ...) { if (!(x)) { INNO_CORE_LOGERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_debugtrap();}}
    #endif
    
#else
    /**
     * @brief Asserts the given condition in release mode. In release mode, this macro does nothing.
     * @param x The condition to be asserted.
     * @param ... The error message format (unused in release mode).
     */
    #define INNO_ASSERT(x, ...)

    /**
     * @brief Asserts the given core condition in release mode. In release mode, this macro does nothing.
     * @param x The condition to be asserted.
     * @param ... The error message format (unused in release mode).
     */
    #define INNO_CORE_ASSERT(x, ...)
#endif

// --------------- Function Binds --------------- //
/**
 * @brief Binds a member function to a specific instance for use with std::function or similar constructs.
 * @param func The member function to be bound.
 * @param instance The instance of the class on which the member function will be called.
 * @return A std::function object that can be called with the specified function and instance.
 */
#define BIND_FUNC(func, instance) std::bind(&func, instance, std::placeholders::_1)

// --------------- Generics --------------- //
/**
 * @brief Encapsulates template definition with a base type constraint.
 * @param T The generate type template.
 * @param base The base type T should inherit from.
 */
#define GENERIC_TYPE(T, base) template<typename T, typename = std::enable_if_t<std::is_base_of<base, T>::value>>
