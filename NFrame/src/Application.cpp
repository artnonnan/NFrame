#include "NFrame/nfpch.h"
#include "NFrame/Core/Application.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/Core/Window.h"
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "NFrame/Core/Input.h"

namespace NFrame
{

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate();
                auto[x, y] = Input::GetMousePosition();
                CORE_TRACE("Mouse Position: ({0}, {1})", x, y);
            }
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