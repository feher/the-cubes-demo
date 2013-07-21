#include "labeldata.h"

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

using namespace std;
using namespace glm;

const string LabelData::compassLabelTextureFile  = "./data/xyz.tga";
const string LabelData::cursorTextureFile  = "./data/cursor.tga";

//    0------2
//    |      |
//    |      |
//    1------3
//

const GLfloat LabelData::m_vertices[] = {
    -1, +1, 0,  -1, -1, 0,  +1, +1, 0,  +1, -1, 0 // front 0-3
};

const GLubyte LabelData::m_elements[] = {
    0, 1, 2, 3
};

LabelData::LabelData(const string& textureFile,
                                   int uvWidthSplit, int uvHeightSplit) {
                                       
    // The texture file can contain multiple labels.
    // Generate UV coordinates for all the labels.
    const auto guard = 0.0f;
    m_uvs = vector<GLfloat>(8 * uvWidthSplit * uvHeightSplit);
    auto du = 1.0f / uvWidthSplit;
    auto dv = 1.0f / uvHeightSplit;
    for (auto i = 0; i < uvHeightSplit; ++i) {
        for (auto j = 0; j < uvWidthSplit; ++j) {
            auto labelNdx = (i * uvWidthSplit + j) * 8;
            m_uvs[labelNdx + 0] = (j + 0) * du; // u
            m_uvs[labelNdx + 1] = (i + 1) * dv; // v
            m_uvs[labelNdx + 2] = (j + 0) * du; // u
            m_uvs[labelNdx + 3] = (i + 0) * dv; // v
            m_uvs[labelNdx + 4] = (j + 1) * du; // u
            m_uvs[labelNdx + 5] = (i + 1) * dv; // v
            m_uvs[labelNdx + 6] = (j + 1) * du; // u
            m_uvs[labelNdx + 7] = (i + 0) * dv; // v
        }
    }
                                       
    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    m_uvBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (8 * uvWidthSplit * uvHeightSplit),
                                  &m_uvs[0], GL_STATIC_DRAW);

    m_elementBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId.id());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_elements), m_elements, GL_STATIC_DRAW);

    m_textureId.generate(GlBuffer::TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_textureId.id());
    if (glfwLoadTexture2D(textureFile.c_str(), 0) == GL_FALSE) {
        throw runtime_error("Cannot load texture from " + textureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
 }
