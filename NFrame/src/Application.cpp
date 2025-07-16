#include "NFrame/nfpch.h"
#include "NFrame/Core/Log.h"
#include "NFrame/Core/Application.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/Core/Window.h"
#include "GLFW/glfw3.h"

namespace NFrame
{
    Application::Application()
    {
       m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {

        std::string input;
        while (m_Running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();

        }
    }
    Application* CreateApplication();
}