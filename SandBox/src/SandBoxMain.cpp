#include "NFrame/nfpch.h"
#include "NFrame.h"
#include "NFrame/Core/EntryPoint.h"


class ExampleLayer : public NFrame::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // CLIENT_INFO("ExampleLayer Update");
        if(NFrame::Input::IsKeyPressed(NF_KEY_TAB)) {
            CLIENT_INFO("Tab key is pressed");
        }
    }

    void OnEvent(NFrame::Event& event) override {
        if(NFrame::EventType::KeyPressed == event.GetEventType()) {
            NFrame::KeyPressedEvent& e = static_cast<NFrame::KeyPressedEvent&>(event);
            CLIENT_INFO("{0}" , (char)e.GetKeyCode());
        }
    }
};

class SandBoxApplication : public NFrame::Application {
public:
    SandBoxApplication() {
        PushLayer(new ExampleLayer());
        PushOverlay(new NFrame::ImGuiLayer());
        CLIENT_INFO("SandBoxApplication created");
    }
    virtual ~SandBoxApplication() {

    }
};

NFrame::Application* NFrame::CreateApplication() {
    return new SandBoxApplication();
}