#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp> // vec*, mat*

// The camera is looking towards its own positive Z axis.
// The Y axis points up and the X axis points right.
class Camera {
public:
    explicit Camera(glm::vec3 position, glm::vec3 angles);
    explicit Camera(glm::vec3 position, glm::mat3 base);

    void updateAngles(const glm::vec3& delta);
    void updatePosition(const glm::vec3& delta);
    const glm::vec3& position() const;
    const glm::mat4& viewMatrix() const;
    const glm::mat3& base() const;

private:
    void updateViewMatrix();

    enum {
        YAW = 0,
        PITCH = 1,
        ROLL = 2
    };
    glm::vec3 m_position;
    glm::mat4 m_viewMatrix;
    glm::mat3 m_base;
};

#endif
