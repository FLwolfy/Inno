#pragma once

#include "spdlog/spdlog.h"

namespace Inno
{
    class Log
    {
    public:
        /**
         * @brief Initializes the logging system.
         */
        static void Init();

        /**
         * @brief Retrieves the core logger instance.
         * @return Reference to the core logger.
         */
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

        /**
         * @brief Retrieves the client logger instance.
         * @return Reference to the client logger.
         */
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// ---------------Core Logs Macros--------------- //
/**
 * @brief Logs a trace message using the core logger.
 */
#define INNO_CORE_LOGTRACE(...) ::Inno::Log::GetCoreLogger()->trace((const std::string)__VA_ARGS__)

/**
 * @brief Logs an info message using the core logger.
 */
#define INNO_CORE_LOGINFO(...)  ::Inno::Log::GetCoreLogger()->info((const std::string)__VA_ARGS__)

/**
 * @brief Logs a warning message using the core logger.
 */
#define INNO_CORE_LOGWARN(...)  ::Inno::Log::GetCoreLogger()->warn((const std::string)__VA_ARGS__)

/**
 * @brief Logs an error message using the core logger.
 */
#define INNO_CORE_LOGERROR(...) ::Inno::Log::GetCoreLogger()->error((const std::string)__VA_ARGS__)

/**
 * @brief Logs a fatal error message using the core logger.
 */
#define INNO_CORE_LOGFATAL(...) ::Inno::Log::GetCoreLogger()->critical((const std::string)__VA_ARGS__)

// ---------------Client Logs Macros--------------- //
/**
 * @brief Logs a trace message using the client logger.
 */
#define INNO_LOGTRACE(...) ::Inno::Log::GetClientLogger()->trace((const std::string)__VA_ARGS__)

/**
 * @brief Logs an info message using the client logger.
 */
#define INNO_LOGINFO(...)  ::Inno::Log::GetClientLogger()->info((const std::string)__VA_ARGS__)

/**
 * @brief Logs a warning message using the client logger.
 */
#define INNO_LOGWARN(...)  ::Inno::Log::GetClientLogger()->warn((const std::string)__VA_ARGS__)

/**
 * @brief Logs an error message using the client logger.
 */
#define INNO_LOGERROR(...) ::Inno::Log::GetClientLogger()->error((const std::string)__VA_ARGS__)

/**
 * @brief Logs a fatal error message using the client logger.
 */
#define INNO_LOGFATAL(...) ::Inno::Log::GetClientLogger()->critical((const std::string)__VA_ARGS__)
