#include "lighttextureprogram.h"

#include <string>
#include <vector>

using namespace std;
using namespace glm;

const string LightTextureProgram::vertexShaderFile = "./shaders/lighttexture.vsh";
const string LightTextureProgram::fragmentShaderFile = "./shaders/lighttexture.fsh";

LightTextureProgram::LightTextureProgram(const string& vertexShaderPrefix,
                                         const string& fragmentShaderPrefix) {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back(vertexShaderPrefix);
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back(fragmentShaderPrefix);
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    const auto p = programId();
    am_vertexPositionId = glGetAttribLocation(p, "am_vertexPosition");
    am_vertexNormalId = glGetAttribLocation(p, "am_vertexNormal");
    a_vertexUvId = glGetAttribLocation(p, "a_vertexUv");
    u_colorId = glGetUniformLocation(p, "u_color");
    u_mvpId = glGetUniformLocation(p, "u_mvp");
    u_mId = glGetUniformLocation(p, "u_m");
    u_vId = glGetUniformLocation(p, "u_v");
    u_mnsId = glGetUniformLocation(p, "u_mns");
    uw_lightPositionId = glGetUniformLocation(p, "uw_lightPosition");
    u_lightColorId = glGetUniformLocation(p, "u_lightColor");
    u_lightPowerId = glGetUniformLocation(p, "u_lightPower");
    u_highlightFactorId = glGetUniformLocation(p, "u_highlightFactor");
    u_textureSamplerId = glGetUniformLocation(p, "u_textureSampler");
    u_materialAmbientFactorId = glGetUniformLocation(p, "u_materialAmbientFactor");
    u_materialSpecularFactorId = glGetUniformLocation(p, "u_materialSpecularFactor");
}

void LightTextureProgram::activate() {
    Program::activate();
}

void LightTextureProgram::configure(TriangleMeshObject& object) {
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &object.programMvp()[0][0]);
    glUniformMatrix4fv(u_mId, 1, GL_FALSE, &object.programModelMatrix()[0][0]);
    glUniformMatrix4fv(u_vId, 1, GL_FALSE, &object.programViewMatrix()[0][0]);
    glUniformMatrix4fv(u_mnsId, 1, GL_FALSE, &object.programUnscaledModelMatrix()[0][0]);
    glUniform3fv(uw_lightPositionId, 1, &object.programLightPos()[0]);
    glUniform3fv(u_lightColorId, 1, &object.programLightColor()[0]);
    glUniform1f(u_lightPowerId, object.programLightPower());
    glUniform1f(u_highlightFactorId, object.programHighlightFactor());
    glUniform4fv(u_materialAmbientFactorId, 1, &object.programMaterialAmbientFactor()[0]);
    glUniform4fv(u_materialSpecularFactorId, 1, &object.programMaterialSpecularFactor()[0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.programTextureId());
    glUniform1i(u_textureSamplerId, 0);

    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glEnableVertexAttribArray(am_vertexPositionId);
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, position)));
    glEnableVertexAttribArray(am_vertexNormalId);
    glVertexAttribPointer(am_vertexNormalId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, normal)));
    glEnableVertexAttribArray(a_vertexUvId);
    glVertexAttribPointer(a_vertexUvId, 2, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, uv)));
}

void LightTextureProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
    glDisableVertexAttribArray(am_vertexNormalId);
    glDisableVertexAttribArray(a_vertexUvId);
}

