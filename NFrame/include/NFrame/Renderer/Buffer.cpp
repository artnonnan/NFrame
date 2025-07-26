#include "NFrame/nfpch.h"
#include "NFrame/Renderer/Buffer.h"
#include "NFrame/Renderer/Renderer.h"

#include "NFrame/Platform/OpenGL/OpenGLBuffer.h"

namespace NFrame
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLVerrtexBuffer(vertices, size);
            case RendererAPI::Vulkan:  CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
            case RendererAPI::DirectX: CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
        }
        CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
            case RendererAPI::Vulkan:  CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
            case RendererAPI::DirectX: CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
        }
        CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}