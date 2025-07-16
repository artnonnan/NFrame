#pragma once

#include "NFrame/nfpch.h"
#include "NFrame/Core/Core.h"
namespace NFrame
{
    class NFRAME_API Log
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

#define CORE_TRACE(...)      ::NFrame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)       ::NFrame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)       ::NFrame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)      ::NFrame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)   ::NFrame::Log::GetCoreLogger()->critical(__VA_ARGS__)  
#define CLIENT_TRACE(...)    ::NFrame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...)     ::NFrame::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...)     ::NFrame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)    ::NFrame::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...) ::NFrame::Log::GetClientLogger()->critical(__VA_ARGS__)