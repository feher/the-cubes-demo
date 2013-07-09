#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "objectdata.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>

class CubeData : public ObjectData {
public:
    CubeData();
    virtual ~CubeData();

    static const GLfloat hoverHighlightFactor;

    static const std::string modelTextureFile;
    static const std::string actionTextureFile;
    static const GLfloat vertices[6 * 4 * 3];
    static const GLfloat normals[6 * 4 * 3];
    static const GLfloat uvs[6 * 4 * 2];
    static const GLubyte triangles[6 * 2 * 3];

    GLuint vertexBufferId;
    GLuint normalBufferId;
    GLuint uvBufferId;
    GLuint elementBufferId;
    GLuint cubeTextureId;
    GLuint actionCubeTextureId;

private:
    void cleanup();
};

#endif
