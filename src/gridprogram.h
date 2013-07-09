#ifndef GRID_PROGRAM_H
#define GRID_PROGRAM_H

#include "objectprogram.h"

class GridProgram : public ObjectProgram {
public:
    explicit GridProgram();

    GLuint am_vertexPositionId;
    GLuint u_colorId;
    GLuint u_mvpId;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;
};

#endif
