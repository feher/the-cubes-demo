#include "shadowmapview.h"

const GLfloat ShadowMapView::m_vertices[] = { 
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
};

ShadowMapView::ShadowMapView() {
    m_vertexBufferId.generate(GlBuffer::BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void ShadowMapView::render() {
    m_program->activate();
    m_program->configure(*this);
    viewport()->activate();

    viewport()->scissor();
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_program->cleanup();
}
