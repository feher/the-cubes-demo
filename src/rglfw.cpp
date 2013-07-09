#include "rglfw.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <stdexcept> // runtime_error

using namespace std;

RGlfw::RGlfw() {
    if (!glfwInit()) {
        throw runtime_error("Cannot init GLFW");
    }
}

RGlfw::~RGlfw() {
    glfwTerminate();
}
