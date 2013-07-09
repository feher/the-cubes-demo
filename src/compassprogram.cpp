#include "compassprogram.h"

#include <string>

using namespace std;

const string CompassProgram::vertexShaderFile = "./shaders/compass.vsh";
const string CompassProgram::fragmentShaderFile = "./shaders/compass.fsh";

CompassProgram::CompassProgram()
    : ObjectProgram(vertexShaderFile, fragmentShaderFile) {
    am_vertexPositionId = glGetAttribLocation(m_program.id(), "am_vertexPosition");
    a_vertexColorId = glGetAttribLocation(m_program.id(), "a_vertexColor");
    u_mvpId = glGetUniformLocation(m_program.id(), "u_mvp");
}
