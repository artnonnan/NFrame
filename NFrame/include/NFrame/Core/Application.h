#pragma once

#include "NFrame/Core/Core.h"

#include "NFrame/Core/Window.h"
#include "NFrame/Core/LayerStack.h"
#include "NFrame/Event/Event.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/ImGui/ImGuiLayer.h"
#include "NFrame/Renderer/Shader.h"

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
        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        unsigned int m_vertextArray, m_vertexBuffer, m_indexBuffer;
        std::unique_ptr<Shader> m_Shader;
    private:
        static Application* s_Instance;
    };

    Application *CreateApplication();
}