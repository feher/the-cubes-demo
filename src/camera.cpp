#include "camera.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // lookAt, rotate

using namespace std;
using namespace glm;

Camera::Camera(vec3 position, vec3 angles)
    : m_position(position),
      m_base(1.0f)
{
    updateAngles(angles);
}

Camera::Camera(vec3 position, mat3 base)
    : m_position(position),
      m_base(base) {
    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    m_viewMatrix = lookAt(m_position, m_position + m_base[2], m_base[1]);
}

// The rotation is done relative to the current local coordinate system
// of the camera.
void Camera::updateAngles(const vec3& delta) {
    const auto& rotRoll = rotate(mat4(1.0f), delta[ROLL], vec3(0, 0, 1));
    const auto& rotPitch = rotate(rotRoll, delta[PITCH], vec3(1, 0, 0));
    const auto& rotYaw = rotate(rotPitch, delta[YAW], vec3(0, 1, 0));
    const auto& B4 = rotYaw;
    auto B3 = mat3( // The new axes relative to camera space (m_base).
        vec3(B4[0][0], B4[0][1], B4[0][2]),  // X axis relative to m_base.
        vec3(B4[1][0], B4[1][1], B4[1][2]),  // Y axis relative to m_base.
        vec3(B4[2][0], B4[2][1], B4[2][2])); // Z axis relative to m_base.
    B3 = m_base * B3; // The new axes relative to world space (3x3 identity matrix).
    m_base[0] = normalize(B3[0]); // New X axis.
    m_base[1] = normalize(B3[1]); // New Y axis.
    m_base[2] = normalize(B3[2]); // New Z axis.
    updateViewMatrix();
}

// The translation is done relative to the current local coordinate system
// of the camera.
void Camera::updatePosition(const vec3& delta) {
    m_position += m_base * delta;
    updateViewMatrix();
}

const vec3& Camera::position() const {
    return m_position;
}

const mat4& Camera::viewMatrix() const {
    return m_viewMatrix;
}

const mat3& Camera::base() const {
    return m_base;
}

