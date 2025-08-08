#include "NFrame/nfpch.h"
#include "NFrame.h"
#include "NFrame/Core/EntryPoint.h"
#include "imgui.h"
#include "NFrame/ImGui/ImGuiLayer.h"

class ExampleLayer : public NFrame::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        
        m_VertexArray.reset(NFrame::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f};

        std::shared_ptr<NFrame::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(NFrame::VertexBuffer::Create(vertices, sizeof(vertices)));

        NFrame::BufferLayout layout = {
            {NFrame::ShaderDataType::Float3, "a_Position"},
            {NFrame::ShaderDataType::Float4, "a_Color"}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<NFrame::IndexBuffer> indexBuffer;
        indexBuffer.reset(NFrame::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_squareVA.reset(NFrame::VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f};
        std::shared_ptr<NFrame::VertexBuffer> squareVB;
        squareVB.reset(NFrame::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({{NFrame::ShaderDataType::Float3, "a_Position"}});
        m_squareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<NFrame::IndexBuffer> squareIB;
        squareIB.reset(NFrame::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_squareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0); 
                color = v_Color;
            }
        )";
        m_Shader.reset(new NFrame::Shader(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection*  vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc2 = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0); 
            }
        )";
        m_BlueShader.reset(new NFrame::Shader(vertexSrc2, fragmentSrc2));
    }

    void OnUpdate(NFrame::Timestep ts) override {

        if(NFrame::Input::IsKeyPressed(NF_KEY_LEFT)){
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        } 
        else if(NFrame::Input::IsKeyPressed(NF_KEY_RIGHT)){
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        } 
        if(NFrame::Input::IsKeyPressed(NF_KEY_UP)){
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        } 
        else  if(NFrame::Input::IsKeyPressed(NF_KEY_DOWN)){
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }

        if(NFrame::Input::IsKeyPressed(NF_KEY_A)){
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        else if(NFrame::Input::IsKeyPressed(NF_KEY_D)){
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        NFrame::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        NFrame::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
        NFrame::Renderer::BeginScene(m_Camera);

        NFrame::Renderer::Submit(m_BlueShader, m_squareVA);
        NFrame::Renderer::Submit(m_Shader, m_VertexArray);

        NFrame::Renderer::EndScene();
    }

    void OnEvent(NFrame::Event& event) override {
    } 



    void OnImGuiRender() override {

    }
private:
    std::shared_ptr<NFrame::Shader> m_Shader;
    std::shared_ptr<NFrame::VertexArray> m_VertexArray;

    std::shared_ptr<NFrame::Shader> m_BlueShader;
    std::shared_ptr<NFrame::VertexArray> m_squareVA;
    NFrame::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 0.05f;
    float m_CameraRotation = 0.1f;
    float m_CameraRotationSpeed = 2.0f;
};

class SandBoxApplication : public NFrame::Application {
public:
    SandBoxApplication() {
        PushLayer(new ExampleLayer());
        CLIENT_INFO("SandBoxApplication created");
    }
    virtual ~SandBoxApplication() {

    }
};

NFrame::Application* NFrame::CreateApplication() {
    return new SandBoxApplication();
}