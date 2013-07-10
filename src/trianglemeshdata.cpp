#include "trianglemeshdata.h"

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*


using namespace std;
using namespace glm;

TriangleMeshData::TriangleMeshData(
    GLfloat hoverHighlightFactor,
    vec3 materialAmbientFactor,
    vec3 materialSpecularFactor,
    const string& textureFile)
    : m_hoverHighlightFactor(hoverHighlightFactor),
      m_materialAmbientFactor(materialAmbientFactor),
      m_materialSpecularFactor(materialSpecularFactor) {
    m_textureId.generate(GlBuffer::TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_textureId.id());
    if (glfwLoadTexture2D(textureFile.c_str(), 0) == GL_FALSE) {
        throw runtime_error("Cannot load texture from " + textureFile);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint TriangleMeshData::textureId() const {
    return m_textureId.id();
}

GLfloat TriangleMeshData::hoverHighlightFactor() const {
    return m_hoverHighlightFactor;
}

const glm::vec3& TriangleMeshData::materialAmbientFactor() const {
    return m_materialAmbientFactor;
}

const glm::vec3& TriangleMeshData::materialSpecularFactor() const {
    return m_materialSpecularFactor;
}
