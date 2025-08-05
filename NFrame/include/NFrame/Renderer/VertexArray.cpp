#include "NFrame/nfpch.h"
#include "VertexArray.h"
#include "NFrame/Renderer/Renderer.h"
#include "NFrame/Platform/OpenGL/OpenGLVertexArray.h"

namespace NFrame {
    VertexArray* VertexArray::Create(){
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }
        CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}