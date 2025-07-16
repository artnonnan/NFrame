#include "Application.h"
#include "Log.h"
extern NFrame::Application* NFrame::CreateApplication();

int main() {
    NFrame::Log::Init();

    auto app = NFrame::CreateApplication();
    app->Run();
    delete app;
    return 0;
}