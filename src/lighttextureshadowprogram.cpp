#include "lighttextureshadowprogram.h"

using namespace glm;

LightTextureShadowProgram::LightTextureShadowProgram()
    : m_lightTextureProgram("./shaders/shadowmapprefix.vsh", "./shaders/shadowmapprefix.fsh") {
    u_shadowTextureSamplerId = m_lightTextureProgram.getUniformLocation("u_shadowTextureSampler");
    u_shadowMvpId = m_lightTextureProgram.getUniformLocation("u_shadowMvp");
    uw_directionalLightDirectionId = m_lightTextureProgram.getUniformLocation("uw_directionalLightDirection");
}

void LightTextureShadowProgram::activate() {
    m_lightTextureProgram.activate();
}

void LightTextureShadowProgram::configure(ModelObject& object) {
    m_lightTextureProgram.configure(object);

    // Shadow MVP translates vectors to [-1, 1]. We need to convert them to [0, 1], so we can
    // use them to look up the shadow map texture.
    static const auto toUV = mat4(
            0.5, 0.0, 0.0, 0.0, 
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
        );
    const auto& shadowMvp = toUV * object.programShadowMvp();
    glUniformMatrix4fv(u_shadowMvpId, 1, GL_FALSE, &shadowMvp[0][0]);

    glUniform3fv(uw_directionalLightDirectionId, 1, &object.programDirectionalLightDirection()[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, object.programShadowTextureId());
    glUniform1i(u_shadowTextureSamplerId, 1);

}

void LightTextureShadowProgram::cleanup() {
    m_lightTextureProgram.cleanup();
}
