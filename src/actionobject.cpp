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
            auto ang = angle();
            ang.y = float((ang.y > 360) ? 0 : (ang.y + deltaTime * rotationSpeed));
            setRotation(ang);

            if (m_pulse == -1.0f) {
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
            auto ang = angle();
            ang.y = float((ang.y > 360) ? 0 : (ang.y + deltaTime * rotationSpeed));
            setRotation(ang);
        }
        break;
    }
}

void ActionObject::render() {
    glDisable(GL_DEPTH_TEST);
    TriangleMeshObject::render();
    glEnable(GL_DEPTH_TEST);
}
