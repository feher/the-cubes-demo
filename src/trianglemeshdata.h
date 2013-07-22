#ifndef TRIANGLE_MESH_DATA_H
#define TRIANGLE_MESH_DATA_H

#include "objectdata.h"
#include "geom.h"
#include "glbuffer.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte
#include <glm/glm.hpp> // vec*, mat*

#include <vector>
#include <string>

class TriangleMeshData : public ObjectData {
public:
    struct VertexData {
        GLfloat position[3];
        GLfloat tangent[3];   // X, up
        GLfloat bitangent[3]; // Y, right
        GLfloat normal[3];    // Z, out
        GLfloat uv[2];
    };

    struct TriangleElement {
        GLubyte a, b, c;
    };

    explicit TriangleMeshData(GLfloat hoverHighlightFactor,
                     glm::vec3 materialAmbientFactor,
                     glm::vec3 materialSpecularFactor,
                     const std::string& textureFile,
                     const std::string& normalMapFile);

    inline GLuint textureId() const;
    inline GLuint normalMapId() const;
    inline GLfloat hoverHighlightFactor() const;
    inline const glm::vec3& materialAmbientFactor() const;
    inline const glm::vec3& materialSpecularFactor() const;

    virtual GLuint vertexBufferId() const = 0;
    virtual GLuint elementBufferId() const = 0;
    virtual GLuint elementCount() const = 0;
    virtual Geom::Sphere boundingSphere(const glm::vec3& position,
                                        GLfloat scale) const = 0;

private:
    GlBuffer m_textureId;
    GlBuffer m_normalMapId;
    GLfloat m_hoverHighlightFactor;
    glm::vec3 m_materialAmbientFactor;
    glm::vec3 m_materialSpecularFactor;
};

GLuint TriangleMeshData::textureId() const {
    return m_textureId.id();
}

GLuint TriangleMeshData::normalMapId() const {
    return m_normalMapId.id();
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

#endif
