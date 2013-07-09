#include "geom.h"

#include <vector>

using namespace std;
using namespace glm;

Geom::Ray Geom::World::ray(
        const vec2& windowSize,
        const vec2& windowPoint,
        const mat4& viewMatrix,
        const mat4& projectionMatrix) {
    assert(windowSize.x > 0 && windowSize.y > 0);
    assert(windowPoint.x >= 0 && windowPoint.y >= 0);

    // Convert from window to [-1, 1] normalized device coodrinates (NDC).
    const auto& ad2 = 2.0f * vec2(windowPoint.x / windowSize.x, windowPoint.y / windowSize.y) - vec2(1, 1);

    // Create two points on the ray at opposite ends (Z axis) of the NDC cube.
    // ad = First point on the ray in NDC.
    // bd = Second point on the ray in NDC.
    const auto& ad = vec4(ad2.x, ad2.y, -1, 1);
    const auto& bd = vec4(ad2.x, ad2.y,  1, 1);

    // Convert the two NDC points into world space.
    const auto& I = inverse(projectionMatrix * viewMatrix);
    const auto& aw = I * ad;
    const auto& bw = I * bd;
    const auto& origin = aw / aw.w;
    const auto& pointOnRay = bw / bw.w;
    const auto& dir = normalize(pointOnRay - origin);
    return Ray(origin, dir);
}

vector<Geom::Intersection> Geom::World::intersect(
                               const Geom::Ray& ray,
                               const Geom::Sphere& sphere) {
    vector<Intersection> intersections;
    // We do the calculations in the model space of the sphere.
    // I.e. The sphere sits at (0, 0, 0). The axes directions of the
    // model space does not matter.
    const auto& rayOrigin = ray.origin - sphere.origin;
    const auto A = dot(ray.direction, ray.direction);
    const auto B = 2.0f * dot(ray.direction, rayOrigin);
    const auto C = dot(rayOrigin, rayOrigin) - (sphere.radius * sphere.radius);
    const auto discriminant = B*B - 4*A*C;
    if (discriminant < 0) {
        return intersections;
    }
    auto q = B < 0 ? ((-B + sqrt(discriminant)) / 2) : ((-B - sqrt(discriminant)) / 2);
    auto t0 = q/A;
    auto t1 = C/q;
    if (t0 > t1) {
        swap(t0, t1);
    }
    intersections.push_back(Intersection(ray.origin + t0 * ray.direction, t0));
    intersections.push_back(Intersection(ray.origin + t1 * ray.direction, t1));
    return intersections;
}
