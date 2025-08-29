#include "NFrame/nfpch.h"
#include "NFrame/Renderer/Texture.h"
#include "NFrame/Renderer/Renderer.h"
#include "NFrame/Renderer/RendererAPI.h"
#include "NFrame/Platform/OpenGL/OpenGLTexture.h"

namespace NFrame {
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);
        }
        return nullptr;
    }
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);
        }
        return nullptr;
    }
}