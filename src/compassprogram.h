#ifndef COMPASS_PROGRAM_H
#define COMPASS_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "compass.h"

class CompassProgram : public Program,
                       public ObjectProgram<Compass> {
public:
    explicit CompassProgram();

    virtual void activate() override;
    virtual void configure(Compass& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLuint am_vertexPositionId;
    GLuint a_vertexColorId;
    GLuint u_mvpId;
};

#endif
