#ifndef OBJECTPROGRAM_H
#define OBJECTPROGRAM_H

#include "shaderprogram.h"

#include <string>

class ObjectProgram {
public:
    explicit ObjectProgram(const std::string& vertexShaderFile,
                           const std::string& fragmentShaderFile);
    virtual ~ObjectProgram();

    void activate();

protected:
    ShaderProgram m_program;
};

#endif
