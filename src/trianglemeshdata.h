#ifndef TRIANGLE_MESH_DATA_H
#define TRIANGLE_MESH_DATA_H

#include "objectdata.h"
#include "geom.h"
#include "glbuffer.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <vector>
#include <string>

class TriangleMeshData : public ObjectData {
public:
    struct VertexData {
        GLfloat position[3];
        GLfloat normal[3];
        GLfloat uv[2];
    };

    struct TriangleElement {
        GLubyte a, b, c;
    };

    explicit TriangleMeshData(GLfloat hoverHighlightFactor,
                     glm::vec3 materialAmbientFactor,
                     glm::vec3 materialSpecularFactor,
                     const std::string& textureFile);

    GLuint textureId() const;
    GLfloat hoverHighlightFactor() const;
    const glm::vec3& materialAmbientFactor() const;
    const glm::vec3& materialSpecularFactor() const;

    virtual GLuint vertexBufferId() const = 0;
    virtual GLuint elementBufferId() const = 0;
    virtual GLuint elementCount() const = 0;
    virtual Geom::Sphere boundingSphere(const glm::vec3& position,
                                        GLfloat scale) const = 0;

private:
    GlBuffer m_textureId;
    GLfloat m_hoverHighlightFactor;
    glm::vec3 m_materialAmbientFactor;
    glm::vec3 m_materialSpecularFactor;
};

#endif
