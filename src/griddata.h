#ifndef GRID_DATA_H
#define GRID_DATA_H

#include "objectdata.h"
#include "glbuffer.h"

#include <GL/glew.h> // GL*

class GridData : public ObjectData {
public:
    explicit GridData();
    
    enum { dimension = 100, vertexCount = dimension * 2 * 2 };
    static const float unitSize;
    static const float lineWidth;

    inline GLuint vertexBufferId() const;

private:
    GLfloat m_vertices[vertexCount * 3];
    GlBuffer m_vertexBufferId;
};

GLuint GridData::vertexBufferId() const {
    return m_vertexBufferId.id();
}

#endif
