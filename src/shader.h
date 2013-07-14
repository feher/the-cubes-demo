#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <vector>

class Shader {
public:
    explicit Shader(GLenum type);
    ~Shader();

    void compile(const std::vector<std::string>& fileNames);
    GLuint id() const;

private:
    GLenum m_type;
    GLuint m_id;

    void cleanup();
};

#endif
