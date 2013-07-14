#include "actionobject.h"

using namespace std;
using namespace glm;

ActionObject::ActionObject(GLfloat scale)
    : m_originalScale(scale),
      m_pulse(-1.0f) {
    setScale(scale);
}

void ActionObject::update(double deltaTime) {
    const auto rotationSpeed = 45;
    const auto pulseSpeed = 700.0f;
    switch (state()) {
    case PRESSED:
        {
            auto ang = angle() + vec3(0, deltaTime * rotationSpeed, 0);
            ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
            setRotation(ang);

            if (m_pulse == -1.0f) {
                // We are entering this state after being in a different state.
                // Let's start pulsating.
                m_pulse = 0;
            }
            m_pulse += float(deltaTime * pulseSpeed);
            auto scaleOffset = 0.2f * -sin(m_pulse * Geom::PI / 180.0f);
            setScale(m_originalScale + scaleOffset);
            if (m_pulse > 360.0f) {
                setScale(m_originalScale);
                m_pulse = -1.0f;
                setState(NONE);
            }
        }
        break;
    default:
        {
            auto ang = angle() + vec3(0, deltaTime * rotationSpeed, 0);
            ang.y = (ang.y > 360.0f) ? fmod(ang.y, 360.0f) : ang.y;
            setRotation(ang);
        }
        break;
    }
}

void ActionObject::render() {
    // Make sure that we render on top of everything.
    viewport()->activate();
    viewport()->scissor();
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    TriangleMeshObject::render();
}
