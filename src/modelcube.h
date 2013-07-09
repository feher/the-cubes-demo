#ifndef MODELCUBE_H
#define MODELCUBE_H

#include "cube.h"

#include <GL/glew.h> // GL*

class ModelCube : public Cube {
public:
    explicit ModelCube(GLfloat scale);

    virtual void update(double deltaTime) override;

private:
    virtual GLuint textureId() const override;

    GLfloat m_pulse;
    GLfloat m_originalScale;
    GLfloat m_rotationSpeedOffset;
};

#endif
