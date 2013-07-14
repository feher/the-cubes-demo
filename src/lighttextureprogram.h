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
};

#endif
