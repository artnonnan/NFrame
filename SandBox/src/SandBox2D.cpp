#include "SandBox2D.h"
#include "NFrame/Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SandBox2D.h"

SandBox2D::SandBox2D()
    : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}
void SandBox2D::OnAttach() {


    m_squareVA = NFrame::VertexArray::Create();
    float squareVertices[5 * 4] = {
           -0.5f, -0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f, 
            0.5f,  0.5f, 0.0f, 
           -0.5f,  0.5f, 0.0f };
    NFrame::Ref<NFrame::VertexBuffer> squareVB;
    squareVB.reset(NFrame::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    squareVB->SetLayout(
        {
            {NFrame::ShaderDataType::Float3, "a_Position"}
        }
        );
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    NFrame::Ref<NFrame::IndexBuffer> squareIB;
    squareIB.reset(NFrame::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = NFrame::Shader::Create("Sandbox/assets/shaders/FlatColor.glsl");

}

void SandBox2D::OnDetach() {

}

void SandBox2D::OnUpdate(NFrame::Timestep ts){
        m_CameraController.OnUpdate(ts);

        
        NFrame::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        NFrame::RenderCommand::Clear();

        NFrame::Renderer::BeginScene(m_CameraController.GetCamera());



        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);



        m_FlatColorShader->Bind();
        NFrame::Renderer::Submit(m_FlatColorShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        NFrame::Renderer::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(NFrame::Event& event) {
    m_CameraController.OnEvent(event);
}