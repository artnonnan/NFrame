#include "NFrame/nfpch.h"
#include "NFrame.h"
#include "NFrame/Core/EntryPoint.h"

class ExampleLayer : public NFrame::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        CLIENT_INFO("ExampleLayer Update");
    }

    void OnEvent(NFrame::Event& event) override {
        CLIENT_TRACE("ExampleLayer Event: {0}", event.ToString());
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