#include "compass.h"

#include <glm/gtc/matrix_transform.hpp> // lookAt

using namespace std;
using namespace glm;

Compass::Compass(shared_ptr<Camera> modelingCamera)
    : m_modelingCamera(modelingCamera) {
}

void Compass::setData(shared_ptr<CompassData> data) {
    m_data = data;
}
void Compass::setProgram(shared_ptr<GridProgram> program) {
    m_program = program;
}

shared_ptr<CompassData> Compass::data() const {
    return m_data;
}

shared_ptr<GridProgram> Compass::program() const {
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

    glEnableVertexAttribArray(m_program->am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBufferId);

    viewport()->activate();

    glLineWidth(m_data->lineWidth);

    // X
    glUniform4fv(m_program->u_colorId, 1, &m_data->colorX[0]);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_LINES, 0, 2);

    // Y
    glUniform4fv(m_program->u_colorId, 1, &m_data->colorY[0]);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(GLfloat)));
    glDrawArrays(GL_LINES, 0, 2);

    // Z
    glUniform4fv(m_program->u_colorId, 1, &m_data->colorZ[0]);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, (void*)(12 * sizeof(GLfloat)));
    glDrawArrays(GL_LINES, 0, 2);

    // Done
    glDisableVertexAttribArray(m_program->am_vertexPositionId);

    glLineWidth(1.0f);
}
