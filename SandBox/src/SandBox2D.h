#pragma once
#include "NFrame.h"
class SandBox2D : public NFrame::Layer
{
public:
    SandBox2D();
    virtual ~SandBox2D() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    void OnUpdate(NFrame::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(NFrame::Event& event) override;
private:
    NFrame::OrthographicCameraController m_CameraController;

    NFrame::Ref<NFrame::VertexArray> m_squareVA;
    NFrame::Ref<NFrame::Shader> m_FlatColorShader;

    NFrame::Ref<NFrame::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};