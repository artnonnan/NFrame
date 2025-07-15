#pragma once
namespace NFrame
{
    class __declspec(dllexport) Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;
        void Start();

    protected:
        virtual void Run();
    };

    Application *CreateApplication();
}