#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader {
public:
    explicit Shader(GLenum type);
    ~Shader();

    void compile(const std::string& fileName);
    GLuint id() const;

private:
    GLenum m_type;
    GLuint m_id;

    void cleanup();
};

#endif
