#ifndef GRID_PROGRAM_H
#define GRID_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "grid.h"

class GridProgram : public Program,
                    public ObjectProgram<Grid> {
public:
    explicit GridProgram();

    virtual void activate() override;
    virtual void configure(Grid& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLint am_vertexPositionId;
    GLint u_colorId;
    GLint u_mvpId;
};

#endif
