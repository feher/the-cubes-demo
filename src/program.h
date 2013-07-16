#ifndef PROGRAM_H
#define PROGRAM_H

#include "shaderprogram.h"

#include <string>
#include <vector>

class Program {
public:
    virtual ~Program();

    void load(const std::vector<std::string>& vertexShaderFiles,
              const std::vector<std::string>& fragmentShaderFiles);

    GLint getAttribLocation(const GLchar *name);
    GLint getUniformLocation(const GLchar *name);

    inline void activate();

private:
    ShaderProgram m_program;
};

void Program::activate() {
    m_program.activate();
}

#endif
