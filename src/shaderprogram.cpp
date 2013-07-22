#include "shaderprogram.h"

#include <GL/glew.h> // GL*
#include <GLFW/glfw3.h> // glfw*

#include <iostream> // cerr, endl
#include <vector>

using namespace std;

const ShaderProgram* ShaderProgram::m_activeShaderProgram = nullptr;

ShaderProgram::~ShaderProgram() {
    cleanup();
}

void ShaderProgram::link(const Shader& vsh, const Shader& fsh) {
    cleanup();

    m_id = glCreateProgram();
    if (m_id == 0) {
        return;
    }

    glAttachShader(m_id, vsh.id());
    glAttachShader(m_id, fsh.id());
    glLinkProgram(m_id);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int infoLogLength = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            vector<char> msg(infoLogLength + 1);
            glGetShaderInfoLog(m_id, infoLogLength, nullptr, &msg[0]);
            cerr << "Shader linker error: " << endl << string(&msg[0]) << endl;
        }
        cleanup();
    }
}

GLuint ShaderProgram::id() const {
    return m_id;
}

void ShaderProgram::cleanup() {
    if (m_id) {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}

void ShaderProgram::activate() const {
    if (m_activeShaderProgram != this) {
        glUseProgram(m_id);
        m_activeShaderProgram = this;
    }
}

