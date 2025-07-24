#include "NFrame/nfpch.h"
#include "NFrame.h"
#include "NFrame/Core/EntryPoint.h"
#include "imgui.h"
#include "NFrame/ImGui/ImGuiLayer.h"

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

    void OnImGuiRender() override {
        ImGui::Begin("Example Layer");
        ImGui::Text("Hello from ExampleLayer!");
        ImGui::End();
    }
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