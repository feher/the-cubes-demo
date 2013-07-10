#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "trianglemeshdata.h"
#include "glbuffer.h"
#include "geom.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GLuint, GLfloat, GLubyte

#include <string>

class CubeData : public TriangleMeshData {
public:
    explicit CubeData(const std::string& textureFile);

    virtual GLuint vertexBufferId() override;
    virtual GLuint elementBufferId() override;
    virtual GLuint elementCount() override;
    virtual Geom::Sphere boundingSphere(const glm::vec3& position,
                                        GLfloat scale) const override;

    static const std::string modelTextureFile;
    static const std::string actionTextureFile;

private:
    static const VertexData m_vertexData[6 * 4];
    static const TriangleElement m_triangles[6 * 4];

    static GlBuffer m_vertexBufferId;
    static GlBuffer m_elementBufferId;
};

#endif
