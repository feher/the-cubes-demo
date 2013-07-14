#ifndef COMPASS_LABEL_DATA_H
#define COMPASS_LABEL_DATA_H

#include "objectdata.h"
#include "glbuffer.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>

class CompassLabelData : public ObjectData {
public:
    CompassLabelData();

    inline GLuint vertexBufferId() const;
    inline GLuint uvBufferId() const;
    inline GLuint elementBufferId() const;
    inline GLuint textureId() const;

private:
    static const std::string m_textureFile;
    static const GLfloat m_vertices[4 * 3];
    static const GLfloat m_uvs[4 * 2 * 3];
    static const GLubyte m_elements[6];

    GlBuffer m_vertexBufferId;
    GlBuffer m_uvBufferId;
    GlBuffer m_elementBufferId;
    GlBuffer m_textureId;
};

GLuint CompassLabelData::vertexBufferId() const {
    return m_vertexBufferId.id();
}

GLuint CompassLabelData::uvBufferId() const {
    return m_uvBufferId.id();
}

GLuint CompassLabelData::elementBufferId() const {
    return m_elementBufferId.id();
}

GLuint CompassLabelData::textureId() const {
    return m_textureId.id();
}

#endif
