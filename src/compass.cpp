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
void Compass::setProgram(shared_ptr<CompassProgram> program) {
    m_program = program;
}

shared_ptr<CompassData> Compass::data() const {
    return m_data;
}

shared_ptr<CompassProgram> Compass::program() const {
    return m_program;
}

mat4 Compass::modelMatrix() {
    // Our model matrix is calculated from the camera's base.
    const auto CB = m_modelingCamera->base();
    return lookAt(vec3(0), CB[2], CB[1]);
}

void Compass::render() {
    m_program->activate();

    const auto M = modelMatrix();
    const auto V = camera()->viewMatrix();
    const auto P = *projectionMatrix();
    auto MVP = P * V * M;
    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);

    viewport()->activate();

    glLineWidth(m_data->lineWidth);

    glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBufferId);

    glEnableVertexAttribArray(m_program->am_vertexPositionId);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(CompassData::VertexData),
                          (void*)offsetof(CompassData::VertexData, position));

    glEnableVertexAttribArray(m_program->a_vertexColorId);
    glVertexAttribPointer(m_program->a_vertexColorId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(CompassData::VertexData),
                          (void*)offsetof(CompassData::VertexData, color));

    glDrawArrays(GL_LINES, 0, 6);

    // Done
    glDisableVertexAttribArray(m_program->am_vertexPositionId);
    glDisableVertexAttribArray(m_program->a_vertexColorId);

    glLineWidth(1.0f);
}
