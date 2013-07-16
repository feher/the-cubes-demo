#include "program.h"

#include <stdexcept>

using namespace std;

Program::~Program() {
}

void Program::load(const vector<string>& vertexShaderFiles,
                   const vector<string>& fragmentShaderFiles) {
    Shader vsh(GL_VERTEX_SHADER);
    vsh.compile(vertexShaderFiles);
    if (vsh.id() == 0) {
        throw runtime_error("Cannot compile vertex shader");
    }
    Shader fsh(GL_FRAGMENT_SHADER);
    fsh.compile(fragmentShaderFiles);
    if (fsh.id() == 0) {
        throw runtime_error("Cannot compile fragment shader");
    }
    m_program.link(vsh, fsh);
    if (m_program.id() == 0) {
        throw runtime_error("Cannot link shader program");
    }
}

GLint Program::getAttribLocation(const GLchar *name) {
    auto id = glGetAttribLocation(m_program.id(), name);
    if (id < 0) {
        throw runtime_error("Cannot get attribute location: " + string(name));
    }
    return id;
}

GLint Program::getUniformLocation(const GLchar *name) {
    auto id = glGetUniformLocation(m_program.id(), name);
    if (id < 0) {
        throw runtime_error("Cannot get uniform location: " + string(name));
    }
    return id;
}
