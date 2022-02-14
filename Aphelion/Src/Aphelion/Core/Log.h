#pragma once
#include "Core.h"

// Enforce at least trace
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace ap
{
class Log
{
public:
    APHELION_API static void Init();

    APHELION_API static std::shared_ptr<spdlog::logger>& GetCoreLogger();
    APHELION_API static std::shared_ptr<spdlog::logger>& GetClientLogger();

private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;
};
} // namespace ap

// Core log macros
#define AP_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::ap::Log::GetCoreLogger(), __VA_ARGS__)
#define AP_CORE_INFO(...) SPDLOG_LOGGER_INFO(::ap::Log::GetCoreLogger(), __VA_ARGS__)
#define AP_CORE_WARN(...) SPDLOG_LOGGER_WARN(::ap::Log::GetCoreLogger(), __VA_ARGS__)
#define AP_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::ap::Log::GetCoreLogger(), __VA_ARGS__)
#define AP_CORE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::ap::Log::GetCoreLogger(), __VA_ARGS__)

// Client log macros
#define AP_CLIENT_TRACE(...) SPDLOG_LOGGER_TRACE(::ap::Log::GetClientLogger(), __VA_ARGS__)
#define AP_CLIENT_INFO(...) SPDLOG_LOGGER_INFO(::ap::Log::GetClientLogger(), __VA_ARGS__)
#define AP_CLIENT_WARN(...) SPDLOG_LOGGER_WARN(::ap::Log::GetClientLogger(), __VA_ARGS__)
#define AP_CLIENT_ERROR(...) SPDLOG_LOGGER_ERROR(::ap::Log::GetClientLogger(), __VA_ARGS__)
#define AP_CLIENT_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::ap::Log::GetClientLogger(), __VA_ARGS__)

// Context base log macros
#ifdef AP_EXPORT
#define AP_TRACE(...) AP_CORE_TRACE(__VA_ARGS__)
#define AP_INFO(...) AP_CORE_INFO(__VA_ARGS__)
#define AP_WARN(...) AP_CORE_WARN(__VA_ARGS__)
#define AP_ERROR(...) AP_CORE_ERROR(__VA_ARGS__)
#define AP_CRITICAL(...) AP_CORE_CRITICAL(__VA_ARGS__)
#else
#define AP_TRACE(...) AP_CLIENT_TRACE(__VA_ARGS__)
#define AP_INFO(...) AP_CLIENT_INFO(__VA_ARGS__)
#define AP_WARN(...) AP_CLIENT_WARN(__VA_ARGS__)
#define AP_ERROR(...) AP_CLIENT_ERROR(__VA_ARGS__)
#define AP_CRITICAL(...) AP_CLIENT_CRITICAL(__VA_ARGS__)
#endif // AP_EXPORT
