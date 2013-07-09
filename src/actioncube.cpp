#include "actioncube.h"

using namespace std;
using namespace glm;

ActionCube::ActionCube(GLfloat scale)
    : m_originalScale(scale) {
    setScale(scale);
}

GLuint ActionCube::uvBufferId() const {
    return data()->uvBufferId;
}

GLuint ActionCube::textureId() const {
    return data()->actionCubeTextureId;
}

void ActionCube::update(double deltaTime) {
    static GLfloat m_pulse = -1.0f;
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

void ActionCube::render() {
    glDisable(GL_DEPTH_TEST);
    Cube::render();
    glEnable(GL_DEPTH_TEST);
}
