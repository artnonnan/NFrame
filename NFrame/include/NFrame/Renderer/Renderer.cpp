#include "NFrame/nfpch.h"
#include "Renderer.h"  
namespace NFrame {

    void Renderer::BeginScene(){

    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
        
}
