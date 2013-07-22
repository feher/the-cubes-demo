#ifndef SPHERE_DATA_H
#define SPHERE_DATA_H

#include "trianglemeshdata.h"
#include "glbuffer.h"

#include <GL/glew.h> // GLuint, GLfloat, GLubyte
#include <glm/glm.hpp> // vec*, mat*

#include <vector>
#include <string>

class SphereData : public TriangleMeshData {
public:
    explicit SphereData(const std::string& textureFile,
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
    static const unsigned int m_segments;
    static const unsigned int m_rings;

    GlBuffer m_vertexBufferId;
    GlBuffer m_elementBufferId;
    std::vector<VertexData> m_vertexData;
    std::vector<TriangleElement> m_triangles;
};

#endif
