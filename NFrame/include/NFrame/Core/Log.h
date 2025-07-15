#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace NFrame
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define NF_CORE_LOG_TRACE(...)      ::NFrame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NF_CORE_LOG_INFO(...)       ::NFrame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NF_CORE_LOG_WARN(...)       ::NFrame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NF_CORE_LOG_ERROR(...)      ::NFrame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NF_CORE_LOG_CRITICAL(...)   ::NFrame::Log::GetCoreLogger()->critical(__VA_ARGS__)  
#define NF_CLIENT_LOG_TRACE(...)    ::NFrame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NF_CLIENT_LOG_INFO(...)     ::NFrame::Log::GetClientLogger()->info(__VA_ARGS__)
#define NF_CLIENT_LOG_WARN(...)     ::NFrame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NF_CLIENT_LOG_ERROR(...)    ::NFrame::Log::GetClientLogger()->error(__VA_ARGS__)
#define NF_CLIENT_LOG_CRITICAL(...) ::NFrame::Log::GetClientLogger()->critical(__VA_ARGS__)