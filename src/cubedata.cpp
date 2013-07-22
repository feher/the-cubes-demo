#include "cubedata.h"

#include <GLFW/glfw3.h> // glfw*
#include <glm/glm.hpp> // vec*, mat*

using namespace std;
using namespace glm;

const string CubeData::modelTextureFile = "./data/modelcube.tga";
const string CubeData::modelNormalFile = "./data/modelcube_normal.tga";
const string CubeData::actionTextureFile = "./data/actioncube.tga";
const string CubeData::actionNormalFile = "./data/actioncube_normal.tga";

//        4------6       10------14        16------18
//      / |    / |      / |    / |        / |    / |
//    0------2   |    8------12  |      17-----19  |
//    |   5 -|---7    |  11 -|---15     |  20 -|---22
//    | /    | /      | /    | /        | /    | /
//    1------3        9------13         21-----23
//

const CubeData::VertexData CubeData::m_vertexData[] = {
    //  position        tangent        bitangent       normal        uv
    { { -1, +1, +1 }, { +1, 0,  0 }, { 0, +1,  0 }, { 0, 0, +1 }, { 0, 1 } },
    { { -1, -1, +1 }, { +1, 0,  0 }, { 0, +1,  0 }, { 0, 0, +1 }, { 0, 0 } },
    { { +1, +1, +1 }, { +1, 0,  0 }, { 0, +1,  0 }, { 0, 0, +1 }, { 1, 1 } },
    { { +1, -1, +1 }, { +1, 0,  0 }, { 0, +1,  0 }, { 0, 0, +1 }, { 1, 0 } }, // front 0-3
    { { -1, +1, -1 }, { -1, 0,  0 }, { 0, +1,  0 }, { 0, 0, -1 }, { 1, 1 } },
    { { -1, -1, -1 }, { -1, 0,  0 }, { 0, +1,  0 }, { 0, 0, -1 }, { 1, 0 } },
    { { +1, +1, -1 }, { -1, 0,  0 }, { 0, +1,  0 }, { 0, 0, -1 }, { 0, 1 } },
    { { +1, -1, -1 }, { -1, 0,  0 }, { 0, +1,  0 }, { 0, 0, -1 }, { 0, 0 } }, // back 4-7
    { { -1, +1, +1 }, {  0, 0, +1 }, { 0, +1,  0 }, { -1, 0, 0 }, { 1, 1 } },
    { { -1, -1, +1 }, {  0, 0, +1 }, { 0, +1,  0 }, { -1, 0, 0 }, { 1, 0 } },
    { { -1, +1, -1 }, {  0, 0, +1 }, { 0, +1,  0 }, { -1, 0, 0 }, { 0, 1 } },
    { { -1, -1, -1 }, {  0, 0, +1 }, { 0, +1,  0 }, { -1, 0, 0 }, { 0, 0 } }, // left 8-11
    { { +1, +1, +1 }, {  0, 0, -1 }, { 0, +1,  0 }, { +1, 0, 0 }, { 0, 1 } },
    { { +1, -1, +1 }, {  0, 0, -1 }, { 0, +1,  0 }, { +1, 0, 0 }, { 0, 0 } },
    { { +1, +1, -1 }, {  0, 0, -1 }, { 0, +1,  0 }, { +1, 0, 0 }, { 1, 1 } },
    { { +1, -1, -1 }, {  0, 0, -1 }, { 0, +1,  0 }, { +1, 0, 0 }, { 1, 0 } }, // right 12-15
    { { -1, +1, -1 }, { +1, 0,  0 }, { 0,  0, -1 }, { 0, +1, 0 }, { 0, 1 } },
    { { -1, +1, +1 }, { +1, 0,  0 }, { 0,  0, -1 }, { 0, +1, 0 }, { 0, 0 } },
    { { +1, +1, -1 }, { +1, 0,  0 }, { 0,  0, -1 }, { 0, +1, 0 }, { 1, 1 } },
    { { +1, +1, +1 }, { +1, 0,  0 }, { 0,  0, -1 }, { 0, +1, 0 }, { 1, 0 } }, // top 16-19
    { { -1, -1, -1 }, { -1, 0,  0 }, { 0,  0, -1 }, { 0, -1, 0 }, { 1, 1 } },
    { { -1, -1, +1 }, { -1, 0,  0 }, { 0,  0, -1 }, { 0, -1, 0 }, { 1, 0 } },
    { { +1, -1, -1 }, { -1, 0,  0 }, { 0,  0, -1 }, { 0, -1, 0 }, { 0, 1 } },
    { { +1, -1, +1 }, { -1, 0,  0 }, { 0,  0, -1 }, { 0, -1, 0 }, { 0, 0 } }, // bottom 20-23
};

const CubeData::TriangleElement CubeData::m_triangles[] = {
    { 0, 1, 2 }, { 1, 3, 2 },
    { 6, 7, 5 }, { 4, 6, 5 },
    { 8, 11, 9 }, { 8, 10, 11 },
    { 12, 13, 15 }, { 12, 15, 14 },
    { 16, 17, 19 }, { 16, 19, 18 },
    { 20, 23, 21 }, { 20, 22, 23 }
};

CubeData::CubeData(const string& textureFile, const string& normalMapFile)
    : TriangleMeshData(2.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.3f, 0.3f, 0.3f),
                       textureFile, normalMapFile) {
    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
    m_elementBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId.id());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_triangles), m_triangles, GL_STATIC_DRAW);
}

GLuint CubeData::vertexBufferId() const {
    return m_vertexBufferId.id();
}

GLuint CubeData::elementBufferId() const {
    return m_elementBufferId.id();
}

GLuint CubeData::elementCount() const {
    // 6 faces, 2 triangles per face, 3 vertex per triangle.
    return 6 * 2 * 3;
}

Geom::Sphere CubeData::boundingSphere(const glm::vec3& position, GLfloat scale) const {
    return Geom::Sphere(vec4(position, 1),
                        scale * sqrt(3.0f));
}
