#include "Application.h"
#include "Log.h"
extern NFrame::Application* NFrame::CreateApplication();

int main() {
    NFrame::Log::Init();
    NF_CORE_LOG_INFO("NFrame Engine Starting...");
    NF_CLIENT_LOG_ERROR("Client Application Starting...");

    auto app = NFrame::CreateApplication();
    app->Start();
    delete app;
    return 0;
}