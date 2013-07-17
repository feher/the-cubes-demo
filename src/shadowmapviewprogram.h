#ifndef SHADOW_MAP_VIEW_PROGRAM_H
#define SHADOW_MAP_VIEW_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "shadowmapview.h"

class ShadowMapViewProgram : public Program,
                             public ObjectProgram<ShadowMapView> {
public:
    explicit ShadowMapViewProgram();

    virtual void activate() override;
    virtual void configure(ShadowMapView& object) override;
    virtual void cleanup() override;

private:
    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLint am_vertexPositionId;
    GLint u_textureSamplerId;
};

#endif
