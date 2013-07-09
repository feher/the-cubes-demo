#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "camera.h"

#include <glm/glm.hpp> // vec

#include <memory>

class PointLight {
public:
    explicit PointLight(glm::vec3 pos, glm::vec3 col, float pow);

    void linkToCamera(std::shared_ptr<Camera> camera);

    glm::vec3 position() const;
    glm::vec3 color() const;
    float power() const;

private:
    std::shared_ptr<Camera> m_camera;
    glm::vec3 m_position;
    glm::vec3 m_color;
    float m_power;
};

#endif
