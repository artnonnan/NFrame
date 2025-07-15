#include "Application.h"
extern NFrame::Application* NFrame::CreateApplication();

int main() {
    auto app = NFrame::CreateApplication();
    app->Start();
    delete app;
    return 0;
}