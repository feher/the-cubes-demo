#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include "trianglemeshobject.h"

#include <GL/glew.h> // GL*

class ModelObject : public TriangleMeshObject {
public:
    explicit ModelObject(GLfloat scale);

    virtual void update(double deltaTime) override;

private:
    GLfloat m_pulse;
    GLfloat m_originalScale;
    GLfloat m_rotationSpeedOffset;
};

#endif
