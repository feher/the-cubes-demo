#include "shader.h"

#include "file.h"

#include <iostream> // cerr, endl
#include <vector>

using namespace std;

Shader::Shader(GLenum type)
    : m_type(type), m_id(0) {
}

Shader::~Shader() {
    cleanup();
}

void Shader::cleanup() {
    if (m_id) {
        glDeleteShader(m_id);
        m_id = 0;
    }
}

void Shader::compile(const string& fileName) {
    cleanup();

    string src = File::loadTextFile(fileName);
    if (src.empty()) {
        return;
    }

    m_id = glCreateShader(m_type);
	    
    // Compile
    char const* psrc = src.c_str();
    glShaderSource(m_id, 1, &psrc, nullptr);
    glCompileShader(m_id);

    // Check
    GLint result = GL_FALSE;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int infoLogLength = 0;
	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
            vector<char> msg(infoLogLength + 1);
            glGetShaderInfoLog(m_id, infoLogLength, nullptr, &msg[0]);
            cerr << "Shader compilation error: " << fileName << endl << string(&msg[0]) << endl;
    	}
        cleanup();
    }
}

GLuint Shader::id() const {
    return m_id;
}
