#include "NFrame/nfpch.h"
#include "NFrame/Core/Log.h"
#include "NFrame/Core/Application.h"
#include "NFrame/Event/ApplicationEvent.h"


namespace NFrame
{
    void Application::Start()
    {
        Run();
    }

    void Application::Run()
    {
        WindowResizeEvent resizeEvent(800, 600);
        CLIENT_TRACE(resizeEvent.ToString());
        // CORE_TRACE("Application started with size: {0}x{1}", resizeEvent.GetWidth(), resizeEvent.GetHeight());

        std::string input;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, input);
            if (input == "q")
            {
                std::cout << "Exiting main loop.\n";
                break;
            }
            std::cout << "You typed: " << input << "\n";
        }
    }
    Application* CreateApplication();
}