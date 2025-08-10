#include "NFrame/nfpch.h"
#include "NFrame/Renderer/Shader.h"
#include "NFrame/Renderer/Renderer.h"
#include "NFrame/Platform/OpenGL/OpenGLShader.h"

namespace NFrame {
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}