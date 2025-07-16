#include "NFrame/nfpch.h"
#include "NFrame.h"
#include "NFrame/Core/EntryPoint.h"

class SandBoxApplication : public NFrame::Application {
public:
    SandBoxApplication() {

    }
    virtual ~SandBoxApplication() {

    }
};

NFrame::Application* NFrame::CreateApplication() {
    return new SandBoxApplication();
}