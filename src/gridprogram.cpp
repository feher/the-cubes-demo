#include "gridprogram.h"

#include <string>

using namespace std;

const string GridProgram::vertexShaderFile = "./shaders/grid.vsh";
const string GridProgram::fragmentShaderFile = "./shaders/grid.fsh";

GridProgram::GridProgram()
    : ObjectProgram(vertexShaderFile, fragmentShaderFile) {
    am_vertexPositionId = glGetAttribLocation(m_program.id(), "am_vertexPosition");
    u_colorId = glGetUniformLocation(m_program.id(), "u_color");
    u_mvpId = glGetUniformLocation(m_program.id(), "u_mvp");
}
