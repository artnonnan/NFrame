#pragma once

#include "NFrame/nfpch.h"
#include "NFrame/Core/Core.h"
#include "Event.h"



namespace NFrame
{
    class NFRAME_API WindowResizeEvent : public Event
    { 
        public:
            WindowResizeEvent(unsigned int width, unsigned int height) 
                : m_Width(width), m_Height(height) {}

                inline unsigned int GetWidth() const { return m_Width; }
                inline unsigned int GetHeight() const { return m_Height; }
                std::string ToString() const override
                {
                    std::stringstream ss;
                    ss << "WindowResizeEvent: " << m_Width << " x " << m_Height;
                    return ss.str();
                }
                EVENT_CLASS_TYPE(WindowResize)
                EVENT_CLASS_CATEGORY(EventCategoryApplication)
        private:
            unsigned int m_Width;
            unsigned int m_Height;
    };

    class NFRAME_API WindowCloseEvent : public Event
    {
        public:
            WindowCloseEvent() {}

            std::string ToString() const override
            {
                return "WindowCloseEvent";
            }
            EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NFRAME_API AppTickEvent : public Event
    {
        public:
            AppTickEvent() {}

            std::string ToString() const override
            {
                return "AppTickEvent";
            }
            EVENT_CLASS_TYPE(AppTick)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NFRAME_API AppUpdateEvent : public Event
    {
        public:
            AppUpdateEvent() {}

            std::string ToString() const override
            {
                return "AppUpdateEvent";
            }
            EVENT_CLASS_TYPE(AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NFRAME_API AppRenderEvent : public Event
    {
        public:
            AppRenderEvent() {}

            std::string ToString() const override
            {
                return "AppRenderEvent";
            }
            EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}