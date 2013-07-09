#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport {
public:
    explicit Viewport(int lx, int ly, int w, int h);

    void activate() const;

    const int x;
    const int y;
    const int width;
    const int height;

private:
    static const Viewport* m_activeViewport;
};

#endif
