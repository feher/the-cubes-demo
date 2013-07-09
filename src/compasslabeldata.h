#ifndef COMPASS_LABEL_DATA_H
#define COMPASS_LABEL_DATA_H

#include "objectdata.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>

class CompassLabelData : public ObjectData {
public:
    CompassLabelData();
    virtual ~CompassLabelData();

    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint elementBufferId;
    GLuint textureId;

private:
    void cleanup();

    static const std::string textureFile;
    static const GLfloat vertices[4 * 3];
    static const GLfloat uvs[4 * 2 * 3];
    static const GLubyte triangles[6];
};

#endif
