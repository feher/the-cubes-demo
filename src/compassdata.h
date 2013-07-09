#ifndef COMPASS_DATA_H
#define COMPASS_DATA_H

#include "objectdata.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GL*

class CompassData : public ObjectData {
public:
    struct VertexData {
        GLfloat position[3];
        GLfloat color[3];
    };

    explicit CompassData();
    
    static const float lineWidth;
    GLuint vertexBufferId;

private:
    static const VertexData data[6];
};

#endif
