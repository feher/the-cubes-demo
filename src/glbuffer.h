#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include <GL/glew.h> // GL*

#include <stdexcept>

class GlBuffer {
public:
    enum Type {
        VAO,
        BUFFER,
        TEXTURE,
        FRAME
    };

    inline explicit GlBuffer();
    inline ~GlBuffer();

    inline void generate(Type type);
    inline GLuint id() const;

private:
    GLuint m_id;
    int m_type;
};

GlBuffer::GlBuffer() : m_id(0), m_type(BUFFER) {
}

GlBuffer::~GlBuffer() {
    if (!m_id) {
        return;
    }
    switch (m_type) {
    case VAO : glDeleteVertexArrays(1, &m_id); break;
    case BUFFER : glDeleteBuffers(1, &m_id); break;
    case TEXTURE : glDeleteTextures(1, &m_id); break;
    case FRAME : glDeleteFramebuffers(1, &m_id); break;
    default : throw std::runtime_error("Unsupported buffer type"); break;
    }
}

void GlBuffer::generate(Type type) {
    switch (type) {
    case VAO : glGenVertexArrays(1, &m_id); break;
    case BUFFER : glGenBuffers(1, &m_id); break;
    case TEXTURE : glGenTextures(1, &m_id); break;
    case FRAME : glGenFramebuffers(1, &m_id); break;
    default : throw std::runtime_error("Unsupported buffer type"); break;
    }    
    m_type = type;
}

GLuint GlBuffer::id() const {
    return m_id;
}


#endif
