#pragma once

#include "NFrame/Renderer/Buffer.h"

namespace NFrame {

    class OpenGLVerrtexBuffer : public VertexBuffer {
        public: 
            OpenGLVerrtexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVerrtexBuffer();
            virtual void Bind() const;
            virtual void Unbind() const;
        private:
            uint32_t m_RendererID;
    };

        class OpenGLIndexBuffer : public IndexBuffer {
        public: 
            OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
            virtual ~OpenGLIndexBuffer();
            virtual void Bind() const;
            virtual void Unbind() const;
            virtual uint32_t GetCount() const { return m_Count; }
        private:
            uint32_t m_RendererID;
            uint32_t m_Count;
    };
}