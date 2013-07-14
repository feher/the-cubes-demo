#include "compass.h"

#include <glm/gtc/matrix_transform.hpp> // lookAt

#include <cstddef> // offsetof

using namespace std;
using namespace glm;

Compass::Compass(shared_ptr<Camera> modelingCamera)
    : m_modelingCamera(modelingCamera) {
}

void Compass::setData(shared_ptr<CompassData> data) {
    m_data = data;
}
void Compass::setProgram(shared_ptr<ObjectProgram<Compass>> program) {
    m_program = program;
}

mat4 Compass::modelMatrix() {
    // Our model matrix is calculated from the camera's base.
    const auto& CB = m_modelingCamera->base();
    // CB[2] : Orientation of Z axis of camera's base in world space.
    // CB[1] : Orientation of Y axis of camera's base in world space.
    // The compass looks in the opposite direction of the camera.
    return lookAt(vec3(0), CB[2], CB[1]);
}

void Compass::render() {
    m_program->activate();
    m_program->configure(*this);

    viewport()->activate();
    // Make sure that we render on top of everything.
    // We need the depth test for the compass axes.
    viewport()->scissor();
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    glLineWidth(m_data->lineWidth);
    glDrawArrays(GL_LINES, 0, 6);
    glLineWidth(1.0f);

    m_program->cleanup();
}
