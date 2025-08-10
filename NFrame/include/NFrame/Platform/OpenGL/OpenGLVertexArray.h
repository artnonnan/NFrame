#pragma once
#include "NFrame/Renderer/VertexArray.h"


namespace NFrame
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() ;
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const NFrame::Ref<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const NFrame::Ref<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<NFrame::Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_vertexBuffers; }
        virtual const NFrame::Ref<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; }
        
    private: 
        uint32_t m_RendererID;
        std::vector<NFrame::Ref<VertexBuffer>> m_vertexBuffers;
        NFrame::Ref<IndexBuffer> m_indexBuffer;
    };

}