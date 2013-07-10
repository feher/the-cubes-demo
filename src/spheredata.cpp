#include "spheredata.h"

#include "geom.h" // PI

#include <GL/glfw.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

#include <cmath> // sin, cos

using namespace std;
using namespace glm;

const string SphereData::modelTextureFile = "./data/modelsphere.tga";
const string SphereData::actionTextureFile = "./data/actionsphere.tga";

const unsigned int SphereData::m_segments = 12;
const unsigned int SphereData::m_rings = 12;

GlBuffer SphereData::m_vertexBufferId;
GlBuffer SphereData::m_elementBufferId;

vector<SphereData::VertexData> SphereData::m_vertexData;
vector<SphereData::TriangleElement> SphereData::m_triangles;

SphereData::SphereData(const string& textureFile)
    : TriangleMeshData(2.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.3f, 0.3f, 0.3f), textureFile) {
    if (m_vertexBufferId.id() == 0) {

        // Generate geometry.

        // For N segments we generate N+1 points to make a full circle.
        // For N rings we generate N+2 points. Two extra for the poles.
        m_vertexData = vector<VertexData>((m_segments + 1) * (m_rings + 2));
        for (auto i = 0u; i < m_rings + 2; ++i) {
            for (auto j = 0u; j < m_segments + 1; ++j) {
                // Calculate the vertex position and normal.
                const auto phi = j * 2 * Geom::PI / m_segments; // phi [0, 360]
                // N rings divide the sphere to N+1 parts.
                const auto theta = (Geom::PI / 2.0f) - (i * Geom::PI / (m_rings + 1)); // theta [90, -90]
                const auto& p = vec3(cos(theta) * cos(phi),
                                     cos(theta) * sin(phi),
                                     sin(theta));
                const auto k = i * (m_segments + 1) + j;
                m_vertexData[k].position[0] = p.x;
                m_vertexData[k].position[1] = p.z;
                m_vertexData[k].position[2] = -p.y;
                // The normal exactly points to the point.
                m_vertexData[k].normal[0] = p.x;
                m_vertexData[k].normal[1] = p.z;
                m_vertexData[k].normal[2] = -p.y;
                // Calculate the UV coordinates.
                auto uv = vec2(j / float(m_segments), i / float(m_rings + 1.0));
                // Things are different at the poles.
                if (i == 0) uv.x -= (1.0f / (2.0f * m_segments));
                if (i == (m_rings + 1)) uv.x += (1.0f / (2.0f * m_segments));
                m_vertexData[k].uv[0] = uv.x;
                m_vertexData[k].uv[1] = 1 - uv.y;
            }
        }

        // We have (segments + 1) * (rings + 2) vertices.
        // For this we need (segments) * (rings + 1) * 2 triangles.
        const auto pseg = m_segments + 1;
        m_triangles = vector<TriangleElement>((m_segments) * (m_rings + 1) * 2);
        auto t = 0;
        for (auto i = 0u; i < m_rings + 1; ++i) {
            for (auto j = 0u; j < m_segments; ++j, t += 2) {
                m_triangles[t].a = i * pseg + j;
                m_triangles[t].b = (i + 1) * pseg + j;
                m_triangles[t].c = i * pseg + (j + 1);
                m_triangles[t + 1].a = i * pseg + (j + 1);
                m_triangles[t + 1].b = (i + 1) * pseg + j;
                m_triangles[t + 1].c = (i + 1) * pseg + (j + 1);
            }
        }
        assert(t == m_triangles.size());

        // Set up vertex arrays.

        m_vertexBufferId.generate(GlBuffer::BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
        glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(VertexData),
                        &m_vertexData[0], GL_STATIC_DRAW);

        m_elementBufferId.generate(GlBuffer::BUFFER);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId.id());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_triangles.size() * sizeof(TriangleElement),
                        &m_triangles[0], GL_STATIC_DRAW);

    }
}

GLuint SphereData::vertexBufferId() {
    return m_vertexBufferId.id();
}

GLuint SphereData::elementBufferId() {
    return m_elementBufferId.id();
}

GLuint SphereData::elementCount() {
    // 3 vertices per triangle.
    return m_triangles.size() * 3;
}

Geom::Sphere SphereData::boundingSphere(const glm::vec3& position, GLfloat scale) const {
    return Geom::Sphere(vec4(position, 1), scale);
}
