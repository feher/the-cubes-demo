#include "cursor.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

void Cursor::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_program->activate();
    m_program->configure(*this);
    viewport()->activate();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr);

    m_program->cleanup();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
