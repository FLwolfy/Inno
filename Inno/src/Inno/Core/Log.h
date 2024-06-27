#pragma once

#include "spdlog/spdlog.h"

namespace Inno
{
	class Log
	{
	public:
		/// <summary>
		/// Initializes the logging system.
		/// </summary>
		static void Init();

		/// <summary>
		/// Retrieves the core logger instance.
		/// </summary>
		/// <returns>Reference to the core logger.</returns>
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/// <summary>
		/// Retrieves the client logger instance.
		/// </summary>
		/// <returns>Reference to the client logger.</returns>
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// ---------------Core Logs Macros--------------- //
/// <summary>
/// Logs a trace message using the core logger.
/// </summary>
#define INNO_CORE_LOGTRACE(...) ::Inno::Log::GetCoreLogger()->trace((std::string)__VA_ARGS__)

/// <summary>
/// Logs an info message using the core logger.
/// </summary>
#define INNO_CORE_LOGINFO(...)  ::Inno::Log::GetCoreLogger()->info((std::string)__VA_ARGS__)

/// <summary>
/// Logs a warning message using the core logger.
/// </summary>
#define INNO_CORE_LOGWARN(...)  ::Inno::Log::GetCoreLogger()->warn((std::string)__VA_ARGS__)

/// <summary>
/// Logs an error message using the core logger.
/// </summary>
#define INNO_CORE_LOGERROR(...) ::Inno::Log::GetCoreLogger()->error((std::string)__VA_ARGS__)

/// <summary>
/// Logs a fatal error message using the core logger.
/// </summary>
#define INNO_CORE_LOGFATAL(...) ::Inno::Log::GetCoreLogger()->critical((std::string)__VA_ARGS__)

// ---------------Client Logs Macros--------------- //
/// <summary>
/// Logs a trace message using the client logger.
/// </summary>
#define INNO_LOGTRACE(...) ::Inno::Log::GetClientLogger()->trace((std::string)__VA_ARGS__)

/// <summary>
/// Logs an info message using the client logger.
/// </summary>
#define INNO_LOGINFO(...)  ::Inno::Log::GetClientLogger()->info((std::string)__VA_ARGS__)

/// <summary>
/// Logs a warning message using the client logger.
/// </summary>
#define INNO_LOGWARN(...)  ::Inno::Log::GetClientLogger()->warn((std::string)__VA_ARGS__)

/// <summary>
/// Logs an error message using the client logger.
/// </summary>
#define INNO_LOGERROR(...) ::Inno::Log::GetClientLogger()->error((std::string)__VA_ARGS__)

/// <summary>
/// Logs a fatal error message using the client logger.
/// </summary>
#define INNO_LOGFATAL(...) ::Inno::Log::GetClientLogger()->critical((std::string)__VA_ARGS__)