#include "compasslabelprogram.h"

#include <string>
#include <vector>

using namespace std;

const string CompassLabelProgram::vertexShaderFile = "./shaders/compasslabel.vsh";
const string CompassLabelProgram::fragmentShaderFile = "./shaders/compasslabel.fsh";

CompassLabelProgram::CompassLabelProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    const auto p = programId();
    am_vertexPositionId = glGetAttribLocation(p, "am_vertexPosition");
    a_vertexUvId = glGetAttribLocation(p, "a_vertexUv");
    u_colorId = glGetUniformLocation(p, "u_color");
    u_mvpId = glGetUniformLocation(p, "u_mvp");
    u_textureSamplerId = glGetUniformLocation(p, "u_textureSampler");
}

void CompassLabelProgram::activate() {
    Program::activate();
}

void CompassLabelProgram::configure(CompassLabel& object) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.programTextureId());

    glUniform1i(u_textureSamplerId, 0);

    const auto& MVP = object.programMvp();
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(a_vertexUvId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programUvBufferId());
    glVertexAttribPointer(a_vertexUvId, 2, GL_FLOAT, GL_FALSE, 0, object.programUvOffset());
}

void CompassLabelProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
    glDisableVertexAttribArray(a_vertexUvId);
}
