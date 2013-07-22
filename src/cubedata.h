#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "trianglemeshdata.h"
#include "glbuffer.h"
#include "geom.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte
#include <glm/glm.hpp> // vec*, mat*

#include <string>

class CubeData : public TriangleMeshData {
public:
    explicit CubeData(const std::string& textureFile,
                      const std::string& normalMapFile);

    virtual GLuint vertexBufferId() const override;
    virtual GLuint elementBufferId() const override;
    virtual GLuint elementCount() const override;
    virtual Geom::Sphere boundingSphere(const glm::vec3& position,
                                        GLfloat scale) const override;

    static const std::string modelTextureFile;
    static const std::string modelNormalFile;
    static const std::string actionTextureFile;
    static const std::string actionNormalFile;

private:
    static const VertexData m_vertexData[6 * 4];
    static const TriangleElement m_triangles[6 * 4];

    GlBuffer m_vertexBufferId;
    GlBuffer m_elementBufferId;
};

#endif
