#include "compasslabeldata.h"

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

using namespace std;
using namespace glm;

const string CompassLabelData::textureFile  = "./data/xyz.tga";

//    0------2
//    |      |
//    |      |
//    1------3
//

// X0Y1   X1Y1  X2Y1  X3Y1
// X0Y0   X1Y0  X2Y0  X3Y0
#define X0 (0.0f  /384.0f)
#define X1 (128.0f/384.0f)
#define X2 (256.0f/384.0f)
#define X3 (384.0f/384.0f)
#define Y0 (0.0f  /128.0f)
#define Y1 (128.0f/128.0f)
const GLfloat CompassLabelData::uvs[] = {
    X0, Y1,  X0, Y0,  X1, Y1,  X1, Y0, // X label
    X1, Y1,  X1, Y0,  X2, Y1,  X2, Y0, // Y label
    X2, Y1,  X2, Y0,  X3, Y1,  X3, Y0  // Z label
};

const GLfloat CompassLabelData::vertices[] = {
    -1, +1, 0,  -1, -1, 0,  +1, +1, 0,  +1, -1, 0 // front 0-3
};

const GLubyte CompassLabelData::elements[] = {
    0, 1, 2, 3
};

CompassLabelData::CompassLabelData() {

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &uvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    if (glfwLoadTexture2D(textureFile.c_str(), 0) == GL_FALSE) {
        cleanup();
        throw runtime_error("Cannot load texture from " + textureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
 }

CompassLabelData::~CompassLabelData() {
    cleanup();
}

void CompassLabelData::cleanup() {
    if (vertexBufferId) {
        glDeleteBuffers(1, &vertexBufferId);
        vertexBufferId = 0;
    }
    if (uvBufferId) {
        glDeleteBuffers(1, &uvBufferId);
        uvBufferId = 0;
    }
    if (elementBufferId) {
        glDeleteBuffers(1, &elementBufferId);
        elementBufferId = 0;
    }
    if (textureId) {
        glDeleteTextures(1, &textureId);
        textureId = 0;
    }
}

