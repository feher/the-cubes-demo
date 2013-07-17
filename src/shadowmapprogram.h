#ifndef SHADOW_MAP_PROGRAM_H
#define SHADOW_MAP_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "modelobject.h"

class ShadowMapProgram : public Program,
                         public ObjectProgram<ModelObject> {
public:
    explicit ShadowMapProgram();

    virtual void activate() override;
    virtual void configure(ModelObject& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLint am_vertexPositionId;
    GLint u_mvpId;
};

#endif
