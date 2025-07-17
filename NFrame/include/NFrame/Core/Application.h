#pragma once

#include "NFrame/Core/Core.h"

#include "NFrame/Core/Window.h"
#include "NFrame/Core/LayerStack.h"
#include "NFrame/Event/Event.h"
#include "NFrame/Event/ApplicationEvent.h"

namespace NFrame
{
    class NFRAME_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    Application *CreateApplication();
}