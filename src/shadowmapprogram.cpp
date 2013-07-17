#include "shadowmapprogram.h"

#include <string>
#include <vector>

using namespace std;

const string ShadowMapProgram::vertexShaderFile = "./shaders/shadowmap.vsh";
const string ShadowMapProgram::fragmentShaderFile = "./shaders/shadowmap.fsh";

ShadowMapProgram::ShadowMapProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    am_vertexPositionId = getAttribLocation("am_vertexPosition");
    u_mvpId = getUniformLocation("u_mvp");
}

void ShadowMapProgram::activate() {
    Program::activate();
}

void ShadowMapProgram::configure(ModelObject& object) {
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &object.programShadowMvp()[0][0]);

    glEnableVertexAttribArray(am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, position)));
}

void ShadowMapProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
}

