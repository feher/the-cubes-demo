#ifndef RGLFW_WINDOW_H
#define RGLFW_WINDOW_H

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

class RGlfwWindow {
public:
    inline explicit RGlfwWindow();
    inline ~RGlfwWindow();

    inline void create(int width, int height, const std::string& title, bool isFullscreen);
    inline GLFWwindow *handle();

private:
    GLFWwindow *m_window;
};

RGlfwWindow::RGlfwWindow()
    : m_window(nullptr) {
}

RGlfwWindow::~RGlfwWindow() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void RGlfwWindow::create(int width, int height, const std::string& title, bool isFullscreen) {
    if (m_window) {
        throw std::runtime_error("A GLFW window already exists");
    }
    m_window =
        glfwCreateWindow(width, height, title.c_str(),
                         isFullscreen ? glfwGetPrimaryMonitor() : nullptr,
                         nullptr);
}

GLFWwindow *RGlfwWindow::handle() {
    return m_window;
}

#endif
