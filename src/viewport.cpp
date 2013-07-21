#include "viewport.h"

const Viewport* Viewport::m_activeViewport = nullptr;

Viewport::Viewport(int lx, int ly, int w, int h)
    : x(lx), y(ly), width(w), height(h) {
}

void Viewport::activate() const {
    if (m_activeViewport != this) {
        glViewport(x, y, width, height);
        m_activeViewport = this;
    }
}

