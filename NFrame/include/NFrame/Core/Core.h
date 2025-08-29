#pragma once
#include <memory>
#ifdef NF_PLATFORM_WINDOWS
    #if defined(NF_BUILD_DLL)
        #define NFRAME_API __declspec(dllexport)
    #elif defined(NF_USE_DLL)
        #define NFRAME_API __declspec(dllimport)
    #else
        #define NFRAME_API
    #endif
#else
    #define NFRAME_API
#endif

#ifdef NF_ENABLE_ASSERTS
    #define CLIENT_ASSERT(x, ...) { if(!(x)) { NFrame::Log::GetClientLogger()->error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define CORE_ASSERT(x, ...) { if(!(x)) { NFrame::Log::GetCoreLogger()->error("Core Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define CLIENT_ASSERT(x, ...)
    #define CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace NFrame {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}