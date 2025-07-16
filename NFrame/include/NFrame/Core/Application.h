#pragma once
#include "NFrame/Core/Core.h"
#include "NFrame/Event/Event.h"

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