#ifndef COMPASS_LABEL_PROGRAM_H
#define COMPASS_LABEL_PROGRAM_H

#include "objectprogram.h"

class CompassLabelProgram : public ObjectProgram {
public:
    explicit CompassLabelProgram();

    GLuint am_vertexPositionId;
    GLuint a_vertexUvId;
    GLuint u_colorId;
    GLuint u_mvpId;
    GLuint u_textureSamplerId;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;
};

#endif
