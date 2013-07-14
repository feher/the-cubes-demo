#include "compassdata.h"

using namespace std;
using namespace glm;

const float CompassData::lineWidth = 4.0f;

const CompassData::VertexData CompassData::m_vertexData[] = {
    { { 0, 0, 0 }, { 1, 0, 0 }, }, // X axis
    { { 1, 0, 0 }, { 1, 0, 0 }, },
    { { 0, 0, 0 }, { 0, 1, 0 }, }, // Y axis
    { { 0, 1, 0 }, { 0, 1, 0 }, },
    { { 0, 0, 0 }, { 0, 0, 1 }, }, // Z axis
    { { 0, 0, 1 }, { 0, 0, 1 }, },
};

CompassData::CompassData() {
    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
}
