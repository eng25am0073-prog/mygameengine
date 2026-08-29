#pragma once

#include <string>

namespace engine::renderer {

class Shader {
public:
    Shader() = default;
    ~Shader() = default;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    bool Create(const std::string& vertexSource, const std::string& fragmentSource);
    void Destroy();

    void Bind() const;
    void SetUniformVec3(const std::string& name, float x, float y, float z) const;

private:
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    bool LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);

    unsigned int m_programId = 0;
};

} // namespace engine::renderer