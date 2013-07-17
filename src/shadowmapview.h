#ifndef SHADOW_MAP_VIEW_H
#define SHADOW_MAP_VIEW_H

#include "object.h"
#include "objectprogram.h"
#include "shadowmap.h"

class ShadowMapView : public Object {
public:
    explicit ShadowMapView();

    inline void setProgram(std::shared_ptr<ObjectProgram<ShadowMapView>> program);
    inline void setShadowMap(std::shared_ptr<const ShadowMap> shadowmap);

    virtual void render() override;

    inline GLuint programVertexBufferId() const;
    inline GLuint programShadowTextureId() const;

private:
    static const GLfloat m_vertices[3 * 6];

    std::shared_ptr<ObjectProgram<ShadowMapView>> m_program;
    std::shared_ptr<const ShadowMap> m_shadowmap;
    GlBuffer m_vertexBufferId;
};

void ShadowMapView::setProgram(std::shared_ptr<ObjectProgram<ShadowMapView>> program) {
    m_program = program;
}

void ShadowMapView::setShadowMap(std::shared_ptr<const ShadowMap> shadowmap) {
    m_shadowmap = shadowmap;
}

GLuint ShadowMapView::programVertexBufferId() const {
    return m_vertexBufferId.id();
}

GLuint ShadowMapView::programShadowTextureId() const {
    return m_shadowmap->shadowTextureId();
}

#endif
