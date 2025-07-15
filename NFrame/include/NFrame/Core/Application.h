#pragma once
#include "NFrame/Core/Core.h"

namespace NFrame
{
    class NFRAME_API Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;
        void Start();

    protected:
        virtual void Run();
    };

    Application *CreateApplication();
}