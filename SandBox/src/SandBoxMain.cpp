#include "NFrame.h"
#include "NFrame/Platform/OpenGL/OpenGLShader.h"
#include "NFrame/Core/EntryPoint.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public NFrame::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        
        m_VertexArray.reset(NFrame::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f};

        NFrame::Ref<NFrame::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(NFrame::VertexBuffer::Create(vertices, sizeof(vertices)));

        NFrame::BufferLayout layout = {
            {NFrame::ShaderDataType::Float3, "a_Position"},
            {NFrame::ShaderDataType::Float4, "a_Color"}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        NFrame::Ref<NFrame::IndexBuffer> indexBuffer;
        indexBuffer.reset(NFrame::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_squareVA.reset(NFrame::VertexArray::Create());
        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f};
        NFrame::Ref<NFrame::VertexBuffer> squareVB;
        squareVB.reset(NFrame::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout(
            {
                {NFrame::ShaderDataType::Float3, "a_Position"},
                {NFrame::ShaderDataType::Float2, "a_TexCoord"}
            }
            );
        m_squareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        NFrame::Ref<NFrame::IndexBuffer> squareIB;
        squareIB.reset(NFrame::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_squareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
        m_Shader.reset(NFrame::Shader::Create(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc2 = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0); 
            }
        )";
        m_BlueShader.reset(NFrame::Shader::Create(vertexSrc2, fragmentSrc2));

        std::string textureVertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        std::string textureFragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            uniform sampler2D u_Texture;

            in vec2 v_TexCoord;

            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }
        )";
        m_TextureShader.reset(NFrame::Shader::Create(textureVertexSrc, textureFragmentSrc));
        m_Texture = NFrame::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");

        m_LogoTexture = NFrame::Texture2D::Create("Sandbox/assets/textures/ChernoLogo.png");
            
        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_BlueShader)->Bind();
        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);


        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 20; x++){

            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

            NFrame::Renderer::Submit(m_BlueShader, m_squareVA, transform);
            }

        }
        m_Texture->Bind();
        NFrame::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_LogoTexture->Bind();
        NFrame::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // NFrame::Renderer::Submit(m_Shader, m_VertexArray);

        NFrame::Renderer::EndScene();
    }

    void OnEvent(NFrame::Event& event) override {
    } 



    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::SliderFloat("Camera Move Speed", &m_CameraMoveSpeed, 0.1f, 20.0f);
        ImGui::SliderFloat("Camera Rotation Speed", &m_CameraRotationSpeed, 10.0f, 500.0f);
        ImGui::End();
    }
private:
    NFrame::Ref<NFrame::Shader> m_Shader;
    NFrame::Ref<NFrame::VertexArray> m_VertexArray;

    NFrame::Ref<NFrame::Texture2D> m_Texture , m_LogoTexture;
    NFrame::Ref<NFrame::Shader> m_BlueShader, m_TextureShader;
    NFrame::Ref<NFrame::VertexArray> m_squareVA;
    NFrame::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.00f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 100.0f;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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