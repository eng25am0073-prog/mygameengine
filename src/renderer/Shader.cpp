#include "renderer/Shader.h"
#include "core/Log.h"

#include <glad/gl.h>

namespace engine::renderer {

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* sourcePointer = source.c_str();
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024] = {};
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        Log::Error("Shader compilation failed (" + std::to_string(type) + "): " + infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool Shader::LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShader);
    glAttachShader(m_programId, fragmentShader);
    glLinkProgram(m_programId);

    int success = 0;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024] = {};
        glGetProgramInfoLog(m_programId, sizeof(infoLog), nullptr, infoLog);
        Log::Error("Shader program link failed: " + std::string(infoLog));
        glDeleteProgram(m_programId);
        m_programId = 0;
        return false;
    }
    return true;
}

bool Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader) {
        return false;
    }

    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return false;
    }

    bool linked = LinkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return linked;
}

void Shader::Destroy()
{
    if (m_programId != 0) {
        glDeleteProgram(m_programId);
        m_programId = 0;
    }
}

void Shader::Bind() const
{
    glUseProgram(m_programId);
}

void Shader::SetUniformVec3(const std::string& name, float x, float y, float z) const
{
    int location = glGetUniformLocation(m_programId, name.c_str());
    if (location == -1) {
        return;
    }
    glUniform3f(location, x, y, z);
}

} // namespace engine::renderer