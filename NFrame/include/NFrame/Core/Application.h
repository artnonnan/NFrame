#pragma once
#include "NFrame/Core/Core.h"
#include "NFrame/Event/Event.h"
#include "NFrame/Core/Window.h"

namespace NFrame
{
    class NFRAME_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();
}