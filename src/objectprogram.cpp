#include "objectprogram.h"

#include <stdexcept>

using namespace std;

ObjectProgram::~ObjectProgram() {
}

ObjectProgram::ObjectProgram(const string& vertexShaderFile,
                             const string& fragmentShaderFile) {
    Shader vsh(GL_VERTEX_SHADER);
    vsh.compile(vertexShaderFile);
    if (vsh.id() == 0) {
        throw runtime_error("Cannot compile vertex shader");
    }
    Shader fsh(GL_FRAGMENT_SHADER);
    fsh.compile(fragmentShaderFile);
    if (fsh.id() == 0) {
        throw runtime_error("Cannot compile fragment shader");
    }
    m_program.link(vsh, fsh);
    if (m_program.id() == 0) {
        throw runtime_error("Cannot link shader program");
    }
}

void ObjectProgram::activate() {
    m_program.activate();
}

