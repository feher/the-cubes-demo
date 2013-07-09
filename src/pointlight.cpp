#include "pointlight.h"

using namespace std;
using namespace glm;

PointLight::PointLight(vec3 pos, vec3 col, float pow)
    : m_position(pos), m_color(col), m_power(pow) {
}

void PointLight::linkToCamera(shared_ptr<Camera> camera) {
    m_camera = camera;
}

vec3 PointLight::position() const {
    vec3 pos;
    if (m_camera) {
        pos = m_camera->position();
    } else {
        pos = m_position;
    }
    return pos;
}

vec3 PointLight::color() const {
    return m_color;
}

float PointLight::power() const {
    return m_power;
}
