#include "compassprogram.h"

#include <string>
#include <vector>

using namespace std;

const string CompassProgram::vertexShaderFile = "./shaders/compass.vsh";
const string CompassProgram::fragmentShaderFile = "./shaders/compass.fsh";

CompassProgram::CompassProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    const auto p = programId();
    am_vertexPositionId = glGetAttribLocation(p, "am_vertexPosition");
    a_vertexColorId = glGetAttribLocation(p, "a_vertexColor");
    u_mvpId = glGetUniformLocation(p, "u_mvp");
}

void CompassProgram::activate() {
    Program::activate();
}

void CompassProgram::configure(Compass& object) {
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &object.programMvp()[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());

    glEnableVertexAttribArray(am_vertexPositionId);
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(CompassData::VertexData),
                          reinterpret_cast<void*>(offsetof(CompassData::VertexData, position)));

    glEnableVertexAttribArray(a_vertexColorId);
    glVertexAttribPointer(a_vertexColorId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(CompassData::VertexData),
                          reinterpret_cast<void*>(offsetof(CompassData::VertexData, color)));
}

void CompassProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
    glDisableVertexAttribArray(a_vertexColorId);
}
