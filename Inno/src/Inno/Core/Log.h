#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

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

    class ILoggable
    {
    public:
        /**
         * @brief The Log out message for this ILoggable type.
         */
        virtual std::string ToString() const = 0;
    };
}

namespace fmt {
    template <typename T>
    struct formatter<T, std::enable_if_t<std::is_base_of<Inno::ILoggable, T>::value, char>> : formatter<std::string> 
    {
        template <typename FormatContext>
        auto format(const Inno::ILoggable& loggable, FormatContext& ctx) -> decltype(ctx.out()) {
            return format_to(ctx.out(), "{}", loggable.ToString());
        }
    };
}


// ---------------Core Logs Macros--------------- //
/**
 * @brief Logs a trace message using the core logger.
 */
#define INNO_CORE_LOGTRACE(...) ::Inno::Log::GetCoreLogger()->trace(__VA_ARGS__)
/**
 * @brief Logs an info message using the core logger.
 */
#define INNO_CORE_LOGINFO(...)  ::Inno::Log::GetCoreLogger()->info(__VA_ARGS__)
/**
 * @brief Logs a warning message using the core logger.
 */
#define INNO_CORE_LOGWARN(...)  ::Inno::Log::GetCoreLogger()->warn(__VA_ARGS__)
/**
 * @brief Logs an error message using the core logger.
 */
#define INNO_CORE_LOGERROR(...) ::Inno::Log::GetCoreLogger()->error(__VA_ARGS__)
/**
 * @brief Logs a fatal error message using the core logger.
 */
#define INNO_CORE_LOGFATAL(...) ::Inno::Log::GetCoreLogger()->critical(__VA_ARGS__)

// ---------------Client Logs Macros--------------- //
/**
 * @brief Logs a trace message using the client logger.
 */
#define INNO_LOGTRACE(...) ::Inno::Log::GetClientLogger()->trace(__VA_ARGS__)
/**
 * @brief Logs an info message using the client logger.
 */
#define INNO_LOGINFO(...)  ::Inno::Log::GetClientLogger()->info(__VA_ARGS__)
/**
 * @brief Logs a warning message using the client logger.
 */
#define INNO_LOGWARN(...)  ::Inno::Log::GetClientLogger()->warn(__VA_ARGS__)
/**
 * @brief Logs an error message using the client logger.
 */
#define INNO_LOGERROR(...) ::Inno::Log::GetClientLogger()->error(__VA_ARGS__)
/**
 * @brief Logs a fatal error message using the client logger.
 */
#define INNO_LOGFATAL(...) ::Inno::Log::GetClientLogger()->critical(__VA_ARGS__)
