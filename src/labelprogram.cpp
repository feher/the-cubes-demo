#include "labelprogram.h"

#include <string>
#include <vector>

using namespace std;

const string LabelProgram::vertexShaderFile = "./shaders/label.vsh";
const string LabelProgram::fragmentShaderFile = "./shaders/label.fsh";

LabelProgram::LabelProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    am_vertexPositionId = getAttribLocation("am_vertexPosition");
    a_vertexUvId = getAttribLocation("a_vertexUv");
    u_mvpId = getUniformLocation("u_mvp");
    u_textureSamplerId = getUniformLocation("u_textureSampler");
}

void LabelProgram::activate() {
    Program::activate();
}

void LabelProgram::configure(CompassLabel& object) {
    configure<CompassLabel>(object);
}

void LabelProgram::configure(Cursor& object) {
    configure<Cursor>(object);
}

void LabelProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
    glDisableVertexAttribArray(a_vertexUvId);
}
