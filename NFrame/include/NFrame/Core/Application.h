#pragma once

#include "NFrame/Core/Core.h"

#include "NFrame/Core/Window.h"
#include "NFrame/Core/LayerStack.h"
#include "NFrame/Event/Event.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/ImGui/ImGuiLayer.h"
#include "NFrame/Renderer/Shader.h"
#include "NFrame/Renderer/Buffer.h"
#include "NFrame/Renderer/VertexArray.h"
#include "NFrame/Renderer/OrthographicCamera.h"

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
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_squareVA;
        OrthographicCamera m_Camera;
    private:
        static Application* s_Instance;
    };

    Application *CreateApplication();
}