#pragma once
#include "NFrame/Core/Core.h"
#include "NFrame/Core/Layer.h"

namespace NFrame
{
    class NFRAME_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        void Begin();
        void End();
 

    private:
        float m_Time = 0.0f;
    };
}