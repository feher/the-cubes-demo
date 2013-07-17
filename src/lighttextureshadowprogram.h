#ifndef LIGHT_TEXTURE_SHADOW_PROGRAM_H
#define LIGHT_TEXTURE_SHADOW_PROGRAM_H

#include "modelobject.h"
#include "lighttextureprogram.h"

class LightTextureShadowProgram : public ObjectProgram<ModelObject> {
public:
    explicit LightTextureShadowProgram();

    virtual void activate() override;
    virtual void configure(ModelObject& object) override;
    virtual void cleanup();

private:
    LightTextureProgram m_lightTextureProgram;

    GLint u_shadowTextureSamplerId;
    GLint u_shadowMvpId;
    GLint uw_directionalLightDirectionId;
};

#endif
