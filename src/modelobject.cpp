#include "modelobject.h"

#include "geom.h" // PI

#include <cmath>     // sin, sqrt

using namespace std;
using namespace glm;

ModelObject::ModelObject(GLfloat scale)
    : m_pulse(0.0f),
      m_originalScale(scale),
      m_rotationSpeedOffset(0.0f) {
    setScale(scale);
}

void ModelObject::update(double deltaTime) {
    const auto rotationSpeed = 35; // degrees/time
    const auto appearingSpeed = 30;
    const auto pulseSpeed = 450;

    switch (state()) {
        case APPEARING:
            {
                if (m_rotationSpeedOffset == 0.0f) {
                    // We are entering this state after being in a different state.
                    setScale(0);
                    m_rotationSpeedOffset = 50.0f;
                }
                m_rotationSpeedOffset -= float(deltaTime * appearingSpeed);
                auto tmpSpeed = rotationSpeed + (m_rotationSpeedOffset * m_rotationSpeedOffset) / 4.0f;
                auto ang = angle() + vec3(deltaTime * tmpSpeed, deltaTime * tmpSpeed, 0);
                ang.x = (ang.x > 360.0f) ? fmod(ang.x, 360.0f) : ang.x;
                ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
                ang.z = (ang.z > 360.0f) ? fmod(ang.z, 360.0f) : ang.z;
                setRotation(ang);
                setScale(clamp(m_originalScale - m_rotationSpeedOffset/50.f, 0.0f, m_originalScale));
                if (m_rotationSpeedOffset <= 0.0) {
                    m_rotationSpeedOffset = 0.0f;
                    setScale(m_originalScale);
                    setState(NONE);
                }
            }
            break;
        case DISAPPEARING:
            {
                if (m_rotationSpeedOffset == 0.0f) {
                    // We are entering this state after being in a different state.
                    m_rotationSpeedOffset = 50.0f;
                }
                m_rotationSpeedOffset -= float(deltaTime * appearingSpeed);
                auto tmp = 50.0f - m_rotationSpeedOffset;
                auto tmpSpeed = rotationSpeed + (tmp * tmp) / 4.0f;
                auto ang = angle() + vec3(deltaTime * tmpSpeed, deltaTime * tmpSpeed, 0);
                ang.x = (ang.x > 360.0f) ? fmod(ang.x, 360.0f) : ang.x;
                ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
                ang.z = (ang.z > 360.0f) ? fmod(ang.z, 360.0f) : ang.z;
                setRotation(ang);
                setScale(clamp(m_originalScale - tmp/50.f, 0.0f, m_originalScale));
                if (m_rotationSpeedOffset <= 0.0) {
                    m_rotationSpeedOffset = 0.0f;
                    setScale(0);
                    setState(DEAD);
                }
            }
            break;
        case HOVERED:
            {
                auto ang = angle() + vec3(deltaTime * rotationSpeed);
                ang.x = (ang.x > 360.0f) ? fmod(ang.x, 360.0f) : ang.x;
                ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
                ang.z = (ang.z > 360.0f) ? fmod(ang.z, 360.0f) : ang.z;
                setRotation(ang);
                m_pulse = float((m_pulse > 360) ? 0 : (m_pulse + deltaTime * pulseSpeed));
                setScale(float(m_originalScale + 0.1 * sin(m_pulse * Geom::PI / 180.0)));
            }
            break;
        case NONE:
            {
                if (m_pulse != 0) {
                    // We were still pulsating. We shouldn't be.
                    // Let's go back to our original scale, but gradually.
                    m_pulse = float((m_pulse > 360) ? 0 : (m_pulse + deltaTime * pulseSpeed));
                    setScale(float(m_originalScale + 0.1 * sin(m_pulse * Geom::PI / 180.0)));
                }
                auto ang = angle() + vec3(deltaTime * rotationSpeed);
                ang.x = (ang.x > 360.0f) ? fmod(ang.x, 360.0f) : ang.x;
                ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
                ang.z = (ang.z > 360.0f) ? fmod(ang.z, 360.0f) : ang.z;
                setRotation(ang);
            }
            break;
        default :
            break;
    }
}
