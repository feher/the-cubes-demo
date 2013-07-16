#include "gridprogram.h"

#include <string>
#include <vector>

using namespace std;

const string GridProgram::vertexShaderFile = "./shaders/grid.vsh";
const string GridProgram::fragmentShaderFile = "./shaders/grid.fsh";

GridProgram::GridProgram() {
    vector<string> vshFiles;
    vector<string> fshFiles;
    vshFiles.push_back("./shaders/prefix.vsh");
    vshFiles.push_back(vertexShaderFile);
    fshFiles.push_back("./shaders/prefix.fsh");
    fshFiles.push_back(fragmentShaderFile);
    load(vshFiles, fshFiles);

    am_vertexPositionId = getAttribLocation("am_vertexPosition");
    u_colorId = getUniformLocation("u_color");
    u_mvpId = getUniformLocation("u_mvp");
}

void GridProgram::activate() {
    Program::activate();
}

void GridProgram::configure(Grid& object) {
    glUniform4fv(u_colorId, 1, &object.programColor()[0]);
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &object.programMvp()[0][0]);

    glEnableVertexAttribArray(am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GridProgram::cleanup() {
    glDisableVertexAttribArray(am_vertexPositionId);
}
