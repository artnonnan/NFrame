#include "Application.h"
#include "Log.h"
extern NFrame::Application* NFrame::CreateApplication();

int main() {
    NFrame::Log::Init();

    auto app = NFrame::CreateApplication();
    app->Start();
    delete app;
    return 0;
}