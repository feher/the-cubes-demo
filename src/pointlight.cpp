#include "pointlight.h"

using namespace std;
using namespace glm;

PointLight::PointLight(vec3 pos, vec3 col, float pow)
    : m_position(pos), m_color(col), m_power(pow) {
}

void PointLight::linkToCamera(shared_ptr<const Camera> camera) {
    m_camera = camera;
}

const vec3& PointLight::position() const {
    return m_camera ? m_camera->position() : m_position;
}

const vec3& PointLight::color() const {
    return m_color;
}

float PointLight::power() const {
    return m_power;
}
