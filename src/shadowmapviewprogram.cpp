#include "shadowmapviewprogram.h"

#include <string>
#include <vector>

using namespace std;

const string ShadowMapViewProgram::vertexShaderFile = "./shaders/shadowmapview.vsh";
const string ShadowMapViewProgram::fragmentShaderFile = "./shaders/shadowmapview.fsh";

ShadowMapViewProgram::ShadowMapViewProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    am_vertexPositionId = getAttribLocation("am_vertexPosition");
    u_textureSamplerId = getUniformLocation("u_textureSampler");
}

void ShadowMapViewProgram::activate() {
    Program::activate();
}

void ShadowMapViewProgram::configure(ShadowMapView& object) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.programShadowTextureId());
    glUniform1i(u_textureSamplerId, 0);

    glEnableVertexAttribArray(am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ShadowMapViewProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
}
