#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "objectdata.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>

class CubeData : public ObjectData {
public:
    struct VertexData {
        GLfloat position[3];
        GLfloat normal[3];
        GLfloat uv[2];
    };

    CubeData();
    virtual ~CubeData();

    static const GLfloat hoverHighlightFactor;

    GLuint vertexBufferId;
    GLuint elementBufferId;
    GLuint cubeTextureId;
    GLuint actionCubeTextureId;

private:
    void cleanup();

    static const std::string modelTextureFile;
    static const std::string actionTextureFile;
    static const VertexData data[6 * 4];
    static const GLubyte triangles[6 * 2 * 3];
};

#endif
