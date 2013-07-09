#ifndef GRID_DATA_H
#define GRID_DATA_H

#include "objectdata.h"

#include <GL/glew.h> // GL*

class GridData : public ObjectData {
public:
    explicit GridData();
    
    enum { dimension = 100, vertexCount = dimension * 2 * 2 };
    static const float unitSize;
    static const float lineWidth;

    GLfloat vertices[vertexCount * 3];
    GLuint vertexBufferId;
};

#endif
