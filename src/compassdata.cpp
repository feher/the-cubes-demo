#include "compassdata.h"

using namespace std;
using namespace glm;

const float CompassData::lineWidth = 4.0f;

const CompassData::VertexData CompassData::vertexData[] = {
    { { 0, 0, 0 }, { 1, 0, 0 }, }, // X axis
    { { 1, 0, 0 }, { 1, 0, 0  },},
    { { 0, 0, 0 }, { 0, 1, 0 }, }, // Y axis
    { { 0, 1, 0 }, { 0, 1, 0 }, },
    { { 0, 0, 0 }, { 0, 0, 1 }, }, // Z axis
    { { 0, 0, 1 }, { 0, 0, 1 }, },
};

CompassData::CompassData() {
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}
