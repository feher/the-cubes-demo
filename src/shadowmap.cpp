#include "shadowmap.h"

#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

using namespace std;
using namespace glm;

const unsigned int ShadowMap::m_frameBufferWidth = 1024;
const unsigned int ShadowMap::m_frameBufferHeight = 1024;

ShadowMap::ShadowMap(vec3 lightDirection)
    : m_lightDirection(lightDirection),
      m_viewport(make_shared<Viewport>(0, 0, m_frameBufferWidth, m_frameBufferHeight)) {

    m_frameBufferId.generate(GlBuffer::FRAME);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId.id());

    m_shadowTextureId.generate(GlBuffer::TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_shadowTextureId.id());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16,
                 m_frameBufferWidth, m_frameBufferHeight,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	 
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           m_shadowTextureId.id(), 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw runtime_error("Cannot create frame buffer for shadow mapping!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::activate() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId.id());
    m_viewport->activate();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::cleanup() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_screenViewport->activate();
}

mat4 ShadowMap::vp() const {
    // The view matrix is from the light's point of view.
    // We use orthographic projection because the light is only directional.
    // The model matrix will be provided by the model.
    const auto dim = 10.0f;
    const auto near = 2.0f;
    const auto& P = ortho(-dim, dim, -dim, dim, near, near + 2.0f * dim);
    if (m_camera) {
        // Up is the camera's Y axis.
        const auto& up = m_camera->base()[1];
        const auto& V =
            lookAt(m_camera->position() + m_camera->base() * m_lightDirection,
                   m_camera->position(), up);
        return P * V;
    }
    const auto& V = lookAt(m_lightDirection, vec3(0, 0, 0), vec3(0, 1, 0));
    return P * V;
}
