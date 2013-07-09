#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

#include <GL/glew.h>

class ShaderProgram {
public:
    ~ShaderProgram();

    void link(const Shader& vsh, const Shader& fsh);
    GLuint id() const;
    void activate();

private:
    void cleanup();

    GLuint m_id;
    static ShaderProgram* m_activeShaderProgram;
};

#endif
