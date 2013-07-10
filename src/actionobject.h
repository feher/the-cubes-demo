#ifndef ACTION_OBJECT_H
#define ACTION_OBJECT_H

#include "trianglemeshobject.h"

#include <GL/glew.h> // GL*

class ActionObject : public TriangleMeshObject {
public:
    explicit ActionObject(GLfloat scale);

    virtual void update(double deltaTime) override;
    virtual void render() override;

private:
    GLfloat m_originalScale;
    GLfloat m_pulse;
};

#endif
