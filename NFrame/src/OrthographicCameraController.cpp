#include "NFrame/nfpch.h"
#include "NFrame/Renderer/OrthographicCamera.h"
#include "NFrame/Core/OrthographicCameraController.h"
#include "NFrame/Core/Input.h"
#include "NFrame/Core/KeyCodes.h"

namespace NFrame {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {

    }


    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if(Input::IsKeyPressed(NF_KEY_A)){
            m_CameraPosition.x -= m_CameraTranslationSpped * ts;
        } 
        else if(Input::IsKeyPressed(NF_KEY_D)){
            m_CameraPosition.x += m_CameraTranslationSpped * ts;
        } 
        if(Input::IsKeyPressed(NF_KEY_W)){
            m_CameraPosition.y += m_CameraTranslationSpped * ts;
        } 
        else if(Input::IsKeyPressed(NF_KEY_S)){
            m_CameraPosition.y -= m_CameraTranslationSpped * ts;
        }
        if(m_Rotation){
            if(Input::IsKeyPressed(NF_KEY_Q)){
                m_CameraRotation += m_CameraRotationSpeed * ts;
            }
            if(Input::IsKeyPressed(NF_KEY_E)){
                m_CameraRotation -= m_CameraRotationSpeed * ts;
            }
            m_Camera.SetRotation(m_CameraRotation);
        }
        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpped = m_ZoomLevel;
        m_CameraRotationSpeed = m_ZoomLevel ;
    }

    void OrthographicCameraController::OnEvent(Event& e){
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e){
        m_ZoomLevel -= e.GetYOffset() * 0.5f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.1f); // Prevent zooming out too far
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e){
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}
