#ifndef FILE_TGA_H
#define FILE_TGA_H

#include <GL/glew.h> // GL*

#include <string>
#include <vector>

namespace File {
    namespace Tga {
        struct Image {
            inline explicit Image() : isValid(false) {}
            bool isValid;
            bool isCompressed;
            GLuint internalFormat; // GL_RGB, GL_RGBA
            GLuint format; // GL_RGB8, GL_RGBA8
            GLuint bpp;
            GLuint width;
            GLuint height;
            std::vector<GLubyte> data;
        };

        bool texImage2d(const std::string& fileName);
        Image load(const std::string& fileName);
    }
}

#endif
