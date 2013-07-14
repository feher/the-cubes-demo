#ifndef COMPASS_DATA_H
#define COMPASS_DATA_H

#include "objectdata.h"
#include "glbuffer.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GL*

class CompassData : public ObjectData {
public:
    struct VertexData {
        GLfloat position[3];
        GLfloat color[3];
    };

    explicit CompassData();

    inline GLuint vertexBufferId() const;
    
    static const float lineWidth;

private:
    static const VertexData m_vertexData[6];

    GlBuffer m_vertexBufferId;
};

GLuint CompassData::vertexBufferId() const {
    return m_vertexBufferId.id();
}

#endif
