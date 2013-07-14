#ifndef COMPASS_LABEL_PROGRAM_H
#define COMPASS_LABEL_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "compasslabel.h"

class CompassLabelProgram : public Program,
                            public ObjectProgram<CompassLabel> {
public:
    explicit CompassLabelProgram();

    virtual void activate() override;
    virtual void configure(CompassLabel& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLuint am_vertexPositionId;
    GLuint a_vertexUvId;
    GLuint u_colorId;
    GLuint u_mvpId;
    GLuint u_textureSamplerId;
};

#endif
