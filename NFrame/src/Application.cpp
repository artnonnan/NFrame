#include "NFrame/Core/Application.h"
#include <string>
#include <iostream>

namespace NFrame
{
    void Application::Start()
    {
        Run();
    }

    void Application::Run()
    {
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