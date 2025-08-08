#include "NFrame/nfpch.h"
#include "NFrame/Core/Application.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/Core/Window.h"
#include "NFrame/Core/Input.h"
#include "NFrame/Renderer/Renderer.h"
#include "NFrame/Renderer/OrthographicCamera.h"
#include <glfw/glfw3.h>
namespace NFrame
{


    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        // CORE_TRACE("Event: {0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled) // If the event is handled, stop processing further
                break;
        }
    }

    void Application::Run()
    {

        std::string input;
        while (m_Running)
        {
            float time = (float) glfwGetTime(); // Platform::GetTime
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }
            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true; // Indicate that the event has been handled
    }
    Application *CreateApplication();
}