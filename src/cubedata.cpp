#include "cubedata.h"

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

using namespace std;
using namespace glm;

const GLfloat CubeData::hoverHighlightFactor = 2.0f;

const string CubeData::modelTextureFile  = "./data/marble512.tga";
const string CubeData::actionTextureFile  = "./data/actioncube.tga";
const vec3 CubeData::materialAmbientFactor = vec3(0.1f, 0.1f, 0.1f);
const vec3 CubeData::materialSpecularFactor = vec3(0.3f, 0.3f, 0.3f);

//        4------6       10------14        16------18
//      / |    / |      / |    / |        / |    / |
//    0------2   |    8------12  |      17-----19  |
//    |   5 -|---7    |  11 -|---15     |  20 -|---22
//    | /    | /      | /    | /        | /    | /
//    1------3        9------13         21-----23
//

const CubeData::VertexData CubeData::vertexData[] = {
    //  position        normal        uv
    { { -1, +1, +1 }, { 0, 0, +1 }, { 0, 1 } },
    { { -1, -1, +1 }, { 0, 0, +1 }, { 0, 0 } },
    { { +1, +1, +1 }, { 0, 0, +1 }, { 1, 1 } },
    { { +1, -1, +1 }, { 0, 0, +1 }, { 1, 0 } }, // front 0-3
    { { -1, +1, -1 }, { 0, 0, -1 }, { 1, 1 } },
    { { -1, -1, -1 }, { 0, 0, -1 }, { 1, 0 } },
    { { +1, +1, -1 }, { 0, 0, -1 }, { 0, 1 } },
    { { +1, -1, -1 }, { 0, 0, -1 }, { 0, 0 } }, // back 4-7
    { { -1, +1, +1 }, { -1, 0, 0 }, { 1, 1 } },
    { { -1, -1, +1 }, { -1, 0, 0 }, { 1, 0 } },
    { { -1, +1, -1 }, { -1, 0, 0 }, { 0, 1 } },
    { { -1, -1, -1 }, { -1, 0, 0 }, { 0, 0 } }, // left 8-11
    { { +1, +1, +1 }, { +1, 0, 0 }, { 0, 1 } },
    { { +1, -1, +1 }, { +1, 0, 0 }, { 0, 0 } },
    { { +1, +1, -1 }, { +1, 0, 0 }, { 1, 1 } },
    { { +1, -1, -1 }, { +1, 0, 0 }, { 1, 0 } }, // right 12-15
    { { -1, +1, -1 }, { 0, +1, 0 }, { 0, 1 } },
    { { -1, +1, +1 }, { 0, +1, 0 }, { 0, 0 } },
    { { +1, +1, -1 }, { 0, +1, 0 }, { 1, 1 } },
    { { +1, +1, +1 }, { 0, +1, 0 }, { 1, 0 } }, // top 16-19
    { { -1, -1, -1 }, { 0, -1, 0 }, { 1, 1 } },
    { { -1, -1, +1 }, { 0, -1, 0 }, { 1, 0 } },
    { { +1, -1, -1 }, { 0, -1, 0 }, { 0, 1 } },
    { { +1, -1, +1 }, { 0, -1, 0 }, { 0, 0 } }, // bottom 20-23
};

const GLubyte CubeData::triangles[] = {
    0, 1, 2, 1, 3, 2,
    6, 7, 5, 4, 6, 5,
    8, 11, 9, 8, 10, 11,
    12, 13, 15, 12, 15, 14,
    16, 17, 19, 16, 19, 18,
    20, 23, 21, 20, 22, 23
};

CubeData::CubeData() {

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    glGenTextures(1, &cubeTextureId);
    glBindTexture(GL_TEXTURE_2D, cubeTextureId);
    if (glfwLoadTexture2D(modelTextureFile.c_str(), 0) == GL_FALSE) {
        cleanup();
        throw runtime_error("Cannot load texture from " + modelTextureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
 
    glGenTextures(1, &actionCubeTextureId);
    glBindTexture(GL_TEXTURE_2D, actionCubeTextureId);
    if (glfwLoadTexture2D(actionTextureFile.c_str(), 0) == GL_FALSE) {
        cleanup();
        throw runtime_error("Cannot load texture from " + actionTextureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

CubeData::~CubeData() {
    cleanup();
}

void CubeData::cleanup() {
    if (vertexBufferId) {
        glDeleteBuffers(1, &vertexBufferId);
        vertexBufferId = 0;
    }
    if (elementBufferId) {
        glDeleteBuffers(1, &elementBufferId);
        elementBufferId = 0;
    }
    if (cubeTextureId) {
        glDeleteTextures(1, &cubeTextureId);
        cubeTextureId = 0;
    }
    if (actionCubeTextureId) {
        glDeleteTextures(1, &actionCubeTextureId);
        actionCubeTextureId = 0;
    }
}

