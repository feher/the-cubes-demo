#ifndef LABEL_DATA_H
#define LABEL_DATA_H

#include "objectdata.h"
#include "glbuffer.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>
#include <vector>

class LabelData : public ObjectData {
public:
    explicit LabelData(const std::string& textureFile,
                       int uvWidthSplit, int uvHeightSplit);

    inline GLuint vertexBufferId() const;
    inline GLuint uvBufferId() const;
    inline GLuint elementBufferId() const;
    inline GLuint textureId() const;

    static const std::string compassLabelTextureFile;
    static const std::string cursorTextureFile;

private:
    static const GLfloat m_vertices[4 * 3];
    static const GLubyte m_elements[6];

    std::vector<GLfloat> m_uvs;
    GlBuffer m_vertexBufferId;
    GlBuffer m_uvBufferId;
    GlBuffer m_elementBufferId;
    GlBuffer m_textureId;
};

GLuint LabelData::vertexBufferId() const {
    return m_vertexBufferId.id();
}

GLuint LabelData::uvBufferId() const {
    return m_uvBufferId.id();
}

GLuint LabelData::elementBufferId() const {
    return m_elementBufferId.id();
}

GLuint LabelData::textureId() const {
    return m_textureId.id();
}

#endif
