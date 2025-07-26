#include "NFrame/nfpch.h"
#include "NFrame/Core/Application.h"
#include "NFrame/Event/ApplicationEvent.h"
#include "NFrame/Core/Window.h"
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "NFrame/Core/Input.h"
#include "glm/glm.hpp"

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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);


        glGenVertexArrays(1, &m_vertextArray);
        glBindVertexArray(m_vertextArray);


        float vertices[] = {
            // positions        // colors
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left - red
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right - green
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top - blue
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;
            out vec3 v_Color;
            void main()
            {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core
            out vec4 color;
            in vec3 v_Color;
            void main()
            {
                color = vec4(v_Color, 1.0); 
            }
        )";
        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_vertextArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate();
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