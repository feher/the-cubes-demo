#include "compasslabel.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

CompassLabel::CompassLabel(std::shared_ptr<Object> compass)
    : m_compass(compass) {
}

void CompassLabel::setData(shared_ptr<CompassLabelData> data) {
    m_data = data;
}

void CompassLabel::setProgram(shared_ptr<CompassLabelProgram> program) {
    m_program = program;
}

void CompassLabel::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Calculate coordinates of axes tips in normalized device coordinates.
    const auto cM = m_compass->modelMatrix();
    const auto cV = m_compass->camera()->viewMatrix();
    const auto cP = (*m_compass->projectionMatrix());
    const auto cMVP = cP * cV * cM;
    const auto xd = cMVP * vec4(1.3f,0,   0,   1);
    const auto yd = cMVP * vec4(0,   1.3f,0,   1);
    const auto zd = cMVP * vec4(0,   0,   1.3f,1);

    m_program->activate();
    viewport()->activate();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_data->textureId);
    glUniform1i(m_program->u_textureSamplerId, 0);

    glEnableVertexAttribArray(m_program->am_vertexPositionId);
    glEnableVertexAttribArray(m_program->a_vertexUvId);

    // X label
    setPosition(vec3(xd.x / xd.w, xd.y / xd.w, 0));
    auto MVP = modelMatrix();
    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBufferId);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->uvBufferId);
    glVertexAttribPointer(m_program->a_vertexUvId, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId);
    glDrawElements(GL_TRIANGLES,
                   6, // 1 face, 6 vertices per face.
                   GL_UNSIGNED_BYTE, nullptr);

    // Y label
    setPosition(vec3(yd.x / yd.w, yd.y / yd.w, 0));
    MVP = modelMatrix();
    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->uvBufferId);
    glVertexAttribPointer(m_program->a_vertexUvId, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 8));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId);
    glDrawElements(GL_TRIANGLES,
                   6, // 1 face, 6 vertices per face.
                   GL_UNSIGNED_BYTE, nullptr);

    // Z label
    setPosition(vec3(zd.x / zd.w, zd.y / zd.w, 0));
    MVP = modelMatrix();
    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->uvBufferId);
    glVertexAttribPointer(m_program->a_vertexUvId, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 16));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId);
    glDrawElements(GL_TRIANGLES,
                   6, // 1 face, 6 vertices per face.
                   GL_UNSIGNED_BYTE, nullptr);

    glDisableVertexAttribArray(m_program->am_vertexPositionId);
    glDisableVertexAttribArray(m_program->a_vertexUvId);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
