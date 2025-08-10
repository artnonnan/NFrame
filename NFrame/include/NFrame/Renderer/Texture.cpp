#include "NFrame/nfpch.h"
#include "NFrame/Renderer/Texture.h"
#include "NFrame/Renderer/Renderer.h"
#include "NFrame/Renderer/RendererAPI.h"
#include "NFrame/Platform/OpenGL/OpenGLTexture.h"

namespace NFrame {
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(path);
        }
        return nullptr;
    }
}