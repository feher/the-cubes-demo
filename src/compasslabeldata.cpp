#include "compasslabeldata.h"

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

using namespace std;
using namespace glm;

const string CompassLabelData::m_textureFile  = "./data/xyz.tga";

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
const GLfloat CompassLabelData::m_uvs[] = {
    X0, Y1,  X0, Y0,  X1, Y1,  X1, Y0, // X label
    X1, Y1,  X1, Y0,  X2, Y1,  X2, Y0, // Y label
    X2, Y1,  X2, Y0,  X3, Y1,  X3, Y0  // Z label
};

const GLfloat CompassLabelData::m_vertices[] = {
    -1, +1, 0,  -1, -1, 0,  +1, +1, 0,  +1, -1, 0 // front 0-3
};

const GLubyte CompassLabelData::m_elements[] = {
    0, 1, 2, 3
};

CompassLabelData::CompassLabelData() {
    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    m_uvBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_uvs), m_uvs, GL_STATIC_DRAW);

    m_elementBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId.id());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_elements), m_elements, GL_STATIC_DRAW);

    m_textureId.generate(GlBuffer::TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_textureId.id());
    if (glfwLoadTexture2D(m_textureFile.c_str(), 0) == GL_FALSE) {
        throw runtime_error("Cannot load texture from " + m_textureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
 }
