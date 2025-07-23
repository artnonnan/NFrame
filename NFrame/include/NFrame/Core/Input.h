#pragma once

#include "NFrame/nfpch.h"
#include "NFrame/Core/Core.h"


namespace NFrame
{
    class NFRAME_API Input {
        public:
            inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
            inline static bool IsMouseButtonPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
            inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
            inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
            inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }
        protected:
            virtual bool IsKeyPressedImpl(int keyCode) = 0;
            virtual bool IsMouseButtonPressedImpl(int button) = 0;
            virtual std::pair<float, float> GetMousePositionImpl() = 0;
            virtual float GetMouseXImpl() = 0;
            virtual float GetMouseYImpl() = 0;
        private:
            static Input* s_Instance;
    };
}