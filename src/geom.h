#ifndef GEOM_H
#define GEOM_H

#include <GL/glew.h> // GL*
#include <glm/glm.hpp> // vec2, mat4

#include <vector>

namespace Geom {
    static const float PI = 3.141592653589f;

    struct Ray {
        inline Ray(glm::vec4 o, glm::vec4 d) : origin(o), direction(d) {}
        glm::vec4 origin;
        glm::vec4 direction;
    };

    struct Sphere {
        inline Sphere(glm::vec4 o, float r) : origin(o), radius(r) {}
        glm::vec4 origin;
        float radius;
    };

    struct Intersection {
        inline Intersection(glm::vec4 ap, float at) : p(ap), t(at) {}
        glm::vec4 p;
        float t;
    };

    namespace World {
        Ray ray(const glm::vec2& windowSize,
                const glm::vec2& windowPoint,
                const glm::mat4& viewMatrix,
                const glm::mat4& projectionMatrix);

        std::vector<Intersection> intersect(const Ray& ray,
                                            const Sphere& sphere);
    }
}

#endif
