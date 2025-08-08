#pragma once
#include "NFrame/Core/Core.h"
#include "NFrame/Event/Event.h"
#include "NFrame/Core/Timestep.h"
namespace NFrame
{

    class NFRAME_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep timestep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}