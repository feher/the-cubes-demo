#include "compasslabel.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

CompassLabel::CompassLabel(std::shared_ptr<Object> compass)
    : m_compass(compass), m_drawState(X_LABEL) {
}

void CompassLabel::setData(shared_ptr<CompassLabelData> data) {
    m_data = data;
}

void CompassLabel::setProgram(shared_ptr<ObjectProgram<CompassLabel>> program) {
    m_program = program;
}

void CompassLabel::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Calculate coordinates of axes tips in normalized device coordinates.
    const auto& cM = m_compass->modelMatrix();
    const auto& cV = m_compass->camera()->viewMatrix();
    const auto& cP = (*m_compass->projectionMatrix());
    const auto& cMVP = cP * cV * cM;
    const auto& xd = cMVP * vec4(1.3f,0,   0,   1);
    const auto& yd = cMVP * vec4(0,   1.3f,0,   1);
    const auto& zd = cMVP * vec4(0,   0,   1.3f,1);

    m_program->activate();
    viewport()->activate();

    m_drawState = X_LABEL;
    setPosition(vec3(xd.x / xd.w, xd.y / xd.w, 0));
    m_program->configure(*this);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr);

    m_drawState = Y_LABEL;
    setPosition(vec3(yd.x / yd.w, yd.y / yd.w, 0));
    m_program->configure(*this);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr);

    m_drawState = Z_LABEL;
    setPosition(vec3(zd.x / zd.w, zd.y / zd.w, 0));
    m_program->configure(*this);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr);

    m_program->cleanup();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
