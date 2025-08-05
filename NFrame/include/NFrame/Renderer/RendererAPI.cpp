#include "NFrame/nfpch.h"
#include "NFrame/Renderer/RendererAPI.h"

namespace NFrame {
    RendererAPI::API RendererAPI::s_API = API::OpenGL; // Default to OpenGL, can be changed based on platform
}