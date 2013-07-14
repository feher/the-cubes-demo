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

    inline void activate();
    inline GLuint programId() const;

private:
    ShaderProgram m_program;
};

void Program::activate() {
    m_program.activate();
}

GLuint Program::programId() const {
    return m_program.id();
}

#endif
