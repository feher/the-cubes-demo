#include "compasslabelprogram.h"


#include <string>

using namespace std;

const string CompassLabelProgram::vertexShaderFile = "./shaders/compasslabel.vsh";
const string CompassLabelProgram::fragmentShaderFile = "./shaders/compasslabel.fsh";

CompassLabelProgram::CompassLabelProgram()
    : ObjectProgram(vertexShaderFile, fragmentShaderFile) {
    am_vertexPositionId = glGetAttribLocation(m_program.id(), "am_vertexPosition");
    a_vertexUvId = glGetAttribLocation(m_program.id(), "a_vertexUv");
    u_colorId = glGetUniformLocation(m_program.id(), "u_color");
    u_mvpId = glGetUniformLocation(m_program.id(), "u_mvp");
    u_textureSamplerId = glGetUniformLocation(m_program.id(), "u_textureSampler");
}
