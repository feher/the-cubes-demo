#ifndef COMPASS_DATA_H
#define COMPASS_DATA_H

#include "objectdata.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GL*

class CompassData : public ObjectData {
public:
    explicit CompassData();
    
    static const float lineWidth;
    static const glm::vec4 colorX;
    static const glm::vec4 colorY;
    static const glm::vec4 colorZ;

    GLfloat vertices[6 * 3];
    GLuint vertexBufferId;
};

#endif
