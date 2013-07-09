#ifndef COMPASS_PROGRAM_H
#define COMPASS_PROGRAM_H

#include "objectprogram.h"

class CompassProgram : public ObjectProgram {
public:
    explicit CompassProgram();

    GLuint am_vertexPositionId;
    GLuint a_vertexColorId;
    GLuint u_mvpId;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;
};

#endif
