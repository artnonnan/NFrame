#include "SandBox2D.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SandBox2D.h"

SandBox2D::SandBox2D()
    : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}
void SandBox2D::OnAttach() {



}

void SandBox2D::OnDetach() {

}

void SandBox2D::OnUpdate(NFrame::Timestep ts){
        m_CameraController.OnUpdate(ts);

        
        NFrame::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        NFrame::RenderCommand::Clear();

        NFrame::Renderer2D::BeginScene(m_CameraController.GetCamera());



        NFrame::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        NFrame::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});

        
        
        NFrame::Renderer2D::EndScene();
        // std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_FlatColorShader)->Bind();
        // std::dynamic_pointer_cast<NFrame::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(NFrame::Event& event) {
    m_CameraController.OnEvent(event);
}