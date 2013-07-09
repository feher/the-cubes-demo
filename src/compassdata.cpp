#include "compassdata.h"

using namespace std;
using namespace glm;

const float CompassData::lineWidth = 4.0f;
const vec4 CompassData::colorX = vec4(1, 0, 0, 1);
const vec4 CompassData::colorY = vec4(0, 1, 0, 1);
const vec4 CompassData::colorZ = vec4(0, 0, 1, 1);

CompassData::CompassData() {
    // Generate vertices

    // X axes
    vertices[0] = 0;    vertices[1] = 0;    vertices[2] = 0;
    vertices[3] = 1;    vertices[4] = 0;    vertices[5] = 0;
    // Y axes
    vertices[6] = 0;    vertices[7] = 0;    vertices[8] = 0;
    vertices[9] = 0;    vertices[10] = 1;   vertices[11] = 0;
    // Z axes
    vertices[12] = 0;   vertices[13] = 0;   vertices[14] = 0;
    vertices[15] = 0;   vertices[16] = 0;   vertices[17] = 1;

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
