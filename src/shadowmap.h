#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include "glbuffer.h"
#include "viewport.h"

#include <glm/glm.hpp> // vec*, mat*

#include <memory>

class ShadowMap {
public:
    explicit ShadowMap(glm::vec3 lightDirection);

    inline void setScreenViewport(std::shared_ptr<Viewport> screenViewport);

    void activate();
    void cleanup();

    inline std::shared_ptr<const Viewport> viewport() const;
    glm::mat4 vp() const;
    inline GLuint shadowTextureId() const;
    inline const glm::vec3& lightDirection() const;

private:
    static const unsigned int m_frameBufferWidth;
    static const unsigned int m_frameBufferHeight;

    glm::vec3 m_lightDirection;
    GlBuffer m_frameBufferId;
    GlBuffer m_shadowTextureId;
    std::shared_ptr<Viewport> m_viewport;
    std::shared_ptr<Viewport> m_screenViewport;
};

void ShadowMap::setScreenViewport(std::shared_ptr<Viewport> screenViewport) {
    m_screenViewport = screenViewport;
}

std::shared_ptr<const Viewport> ShadowMap::viewport() const {
    return m_viewport;
}

GLuint ShadowMap::shadowTextureId() const {
    return m_shadowTextureId.id();
}

const glm::vec3& ShadowMap::lightDirection() const {
    return m_lightDirection;
}

#endif
