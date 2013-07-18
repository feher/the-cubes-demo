#ifndef COMPASS_H
#define COMPASS_H

#include "camera.h"
#include "object.h"
#include "compassdata.h"
#include "objectprogram.h"

#include <glm/glm.hpp> // vec*, mat*

#include <memory> // shared_ptr

class Compass : public Object {
public:
    Compass(std::shared_ptr<const Camera> modelingCamera);

    void setData(std::shared_ptr<const CompassData> data);
    void setProgram(std::shared_ptr<ObjectProgram<Compass>> program);

    virtual glm::mat4 modelMatrix() override;
    virtual void render() override;

    inline glm::mat4 programMvp();
    inline GLuint programVertexBufferId() const;

private:
    std::shared_ptr<const Camera> m_modelingCamera;
    std::shared_ptr<const CompassData> m_data;
    std::shared_ptr<ObjectProgram<Compass>> m_program;
};

glm::mat4 Compass::programMvp() {
    const auto& M = modelMatrix();
    const auto& V = camera()->viewMatrix();
    const auto& P = *projectionMatrix();
    return (P * V * M);
}

GLuint Compass::programVertexBufferId() const {
    return m_data->vertexBufferId();
}

#endif
