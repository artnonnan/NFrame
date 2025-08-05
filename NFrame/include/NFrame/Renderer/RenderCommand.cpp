#include "NFrame/nfpch.h"
#include "NFrame/Renderer/RenderCommand.h"
#include "NFrame/Platform/OpenGL/OpenGLRendererAPI.h"
namespace NFrame {
    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::GetAPI() == RendererAPI::API::OpenGL ? new OpenGLRendererAPI() : nullptr;
}
