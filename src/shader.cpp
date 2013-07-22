#include "shader.h"

#include "filetext.h"

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

void Shader::compile(const vector<string>& fileNames) {
    cleanup();

    // Load from files.
    string source;
    for (const auto& f : fileNames) {
        const string& src = File::Text::load(f);
        if (!src.empty()) {
            source += src + "\n";
        }
    }
    if (source.empty()) {
        return;
    }

    // Create
    m_id = glCreateShader(m_type);
	    
    // Compile
    const char* sp = source.c_str();
    glShaderSource(m_id, 1, &sp, nullptr);
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
            cerr << "Shader source: " << endl
                 << source << endl
                 << "Shader compilation error: " << endl
                 << string(&msg[0]) << endl;
    	}
        cleanup();
    }
}

GLuint Shader::id() const {
    return m_id;
}
