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
        vertices[o + 0] = x;
        vertices[o + 1] = y;
        vertices[o + 2] = z;
        x = +(dimension * unitSize / 2.0f);
        vertices[o + 3] = x;
        vertices[o + 4] = y;
        vertices[o + 5] = z;
    }

    // Columns
    for (int i = 0; i < dimension; ++i, o += 6) {
        x = (i * unitSize) - (dimension * unitSize / 2.0f);
        z = -(dimension * unitSize / 2.0f);
        y = 0;
        vertices[o + 0] = x;
        vertices[o + 1] = y;
        vertices[o + 2] = z;
        z = +(dimension * unitSize / 2.0f);
        vertices[o + 3] = x;
        vertices[o + 4] = y;
        vertices[o + 5] = z;
    }
    assert(o == vertexCount * 3);

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
