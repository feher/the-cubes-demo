#ifndef LIGHT_TEXTURE_PROGRAM_H
#define LIGHT_TEXTURE_PROGRAM_H

#include "objectprogram.h"

class LightTextureProgram : public ObjectProgram {
public:
    explicit LightTextureProgram();

    GLuint am_vertexPositionId;
    GLuint am_vertexNormalId;
    GLuint a_vertexUvId;
    GLuint u_colorId;
    GLuint u_mvpId;
    GLuint u_mId;
    GLuint u_vId;
    GLuint u_mnsId;
    GLuint uw_lightPositionId;
    GLuint u_lightColorId;
    GLuint u_lightPowerId;
    GLuint u_highlightFactorId;
    GLuint u_textureSamplerId;
    GLuint u_materialAmbientFactorId;
    GLuint u_materialSpecularFactorId;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;
};

#endif
