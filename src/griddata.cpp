#include "griddata.h"

#include <cassert>

using namespace std;

const float GridData::unitSize = 0.5f;
const float GridData::lineWidth = 0.1f;

GridData::GridData() {
    // Generate vertices
    int o = 0;
    GLfloat x = 0, y = 0, z = 0;

    // Rows
    for (int i = 0; i < dimension; ++i, o += 6) {
        x = -(dimension * unitSize / 2.0f);
        z = (i * unitSize) - (dimension * unitSize / 2.0f);
        y = 0;
        m_vertices[o + 0] = x;
        m_vertices[o + 1] = y;
        m_vertices[o + 2] = z;
        x = +(dimension * unitSize / 2.0f);
        m_vertices[o + 3] = x;
        m_vertices[o + 4] = y;
        m_vertices[o + 5] = z;
    }

    // Columns
    for (int i = 0; i < dimension; ++i, o += 6) {
        x = (i * unitSize) - (dimension * unitSize / 2.0f);
        z = -(dimension * unitSize / 2.0f);
        y = 0;
        m_vertices[o + 0] = x;
        m_vertices[o + 1] = y;
        m_vertices[o + 2] = z;
        z = +(dimension * unitSize / 2.0f);
        m_vertices[o + 3] = x;
        m_vertices[o + 4] = y;
        m_vertices[o + 5] = z;
    }
    assert(o == vertexCount * 3);

    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}
