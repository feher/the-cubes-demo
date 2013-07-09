#include "cubeprogram.h"

#include <string>

using namespace std;

const string CubeProgram::vertexShaderFile = "./shaders/cube.vsh";
const string CubeProgram::fragmentShaderFile = "./shaders/cube.fsh";

CubeProgram::CubeProgram()
    : ObjectProgram(vertexShaderFile, fragmentShaderFile) {
    am_vertexPositionId = glGetAttribLocation(m_program.id(), "am_vertexPosition");
    am_vertexNormalId = glGetAttribLocation(m_program.id(), "am_vertexNormal");
    a_vertexUvId = glGetAttribLocation(m_program.id(), "a_vertexUv");
    u_colorId = glGetUniformLocation(m_program.id(), "u_color");
    u_mvpId = glGetUniformLocation(m_program.id(), "u_mvp");
    u_mId = glGetUniformLocation(m_program.id(), "u_m");
    u_vId = glGetUniformLocation(m_program.id(), "u_v");
    u_mnsId = glGetUniformLocation(m_program.id(), "u_mns");
    uw_lightPositionId = glGetUniformLocation(m_program.id(), "uw_lightPosition");
    u_lightColorId = glGetUniformLocation(m_program.id(), "u_lightColor");
    u_lightPowerId = glGetUniformLocation(m_program.id(), "u_lightPower");
    u_highlightFactorId = glGetUniformLocation(m_program.id(), "u_highlightFactor");
    u_textureSamplerId = glGetUniformLocation(m_program.id(), "u_textureSampler");
    u_materialAmbientFactorId = glGetUniformLocation(m_program.id(), "u_materialAmbientFactor");
    u_materialSpecularFactorId = glGetUniformLocation(m_program.id(), "u_materialSpecularFactor");
}