#pragma once

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

#define BIT(x) (1 << x)