#pragma once

#include <string>
#include <glm/glm.hpp>
namespace NFrame
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, std::string& fragmentSrc);
        ~Shader();
        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name,const glm::mat4& matrix);
    private:
        unsigned int m_RendererID;
        // std::string m_VertexSrc;
        // std::string m_FragmentSrc;

        // void CompileShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        // unsigned int CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        // void DeleteShader();
    };
}