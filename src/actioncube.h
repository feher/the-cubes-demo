#ifndef ACTION_CUBE_H
#define ACTION_CUBE_H

#include "cube.h"

#include <GL/glew.h> // GL*

class ActionCube : public Cube {
public:
    explicit ActionCube(GLfloat scale);

    virtual void update(double deltaTime) override;
    virtual void render() override;

private:
    virtual GLuint textureId() const override;

    GLfloat m_originalScale;
};

#endif
