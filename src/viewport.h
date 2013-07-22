#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <GL/glew.h> // GL*
#include <glm/glm.hpp> // vec*, mat*

class Viewport {
public:
    explicit Viewport(int lx, int ly, int w, int h);

    void activate() const;
    inline void scissor() const;
    inline glm::vec2 positionFromScreen(const glm::vec2& screenPos,
                                        unsigned int screenHeight) const;

    const int x;
    const int y;
    const int width;
    const int height;

private:
    static const Viewport* m_activeViewport;
};

void Viewport::scissor() const {
    glScissor(x, y, width, width);
}

glm::vec2 Viewport::positionFromScreen(const glm::vec2& screenPos, unsigned int screenHeight) const {
    // The screen position is in physical screen dimensions.
    // The screen position's Y axis points down, but the viewport's Y axis
    // points up. So we must invert it.
    return glm::vec2(screenPos.x - x, screenHeight - screenPos.y - y);
}

#endif
