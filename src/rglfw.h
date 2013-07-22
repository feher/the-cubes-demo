#ifndef RGLFW_H
#define RGLFW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h> // glfw*

#include <stdexcept> // runtime_error

class RGlfw {
public:
    inline explicit RGlfw();
    inline ~RGlfw();
};

RGlfw::RGlfw() {
    if (!glfwInit()) {
        throw std::runtime_error("Cannot init GLFW");
    }
}

RGlfw::~RGlfw() {
    glfwTerminate();
}

#endif
