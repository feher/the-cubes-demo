#ifndef LIGHT_TEXTURE_PROGRAM_H
#define LIGHT_TEXTURE_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "trianglemeshobject.h"

#include <string>

class LightTextureProgram : public Program,
                            public ObjectProgram<TriangleMeshObject> {
public:
    explicit LightTextureProgram(const std::string& vertexShaderPrefix = "./shaders/prefix.vsh",
                                 const std::string& fragmentShaderPrefix = "./shaders/prefix.fsh");

    virtual void activate() override;
    virtual void configure(TriangleMeshObject& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLint am_vertexPositionId;
    GLint am_vertexNormalId;
    GLint am_vertexTangentId;
    GLint am_vertexBitangentId;
    GLint a_vertexUvId;
    GLint u_mvpId;
    GLint u_mId;
    GLint u_vId;
    GLint u_mnsId;
    GLint uw_lightPositionId;
    GLint u_lightColorId;
    GLint u_lightPowerId;
    GLint u_highlightFactorId;
    GLint u_textureSamplerId;
    GLint u_normalSamplerId;
    GLint u_materialAmbientFactorId;
    GLint u_materialSpecularFactorId;
};

#endif
