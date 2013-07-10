#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include <GL/glew.h> // GL*

#include <stdexcept>

class GlBuffer {
public:
    enum Type {
        TEXTURE,
        BUFFER
    };

    inline explicit GlBuffer();
    inline ~GlBuffer();

    inline void generate(Type type);
    inline GLuint id() const;

private:
    GLuint m_id;
};

GlBuffer::GlBuffer() : m_id(0) {
}

GlBuffer::~GlBuffer() {
    if (m_id) {
        glDeleteBuffers(1, &m_id);
    }
}

void GlBuffer::generate(Type type) {
    switch (type) {
    case BUFFER : glGenBuffers(1, &m_id); break;
    case TEXTURE : glGenTextures(1, &m_id); break;
    default : throw std::runtime_error("Unsupported buffer type"); break;
    }    
}

GLuint GlBuffer::id() const {
    return m_id;
}


#endif
