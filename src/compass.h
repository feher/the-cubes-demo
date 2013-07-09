#ifndef COMPASS_H
#define COMPASS_H

#include "camera.h"
#include "object.h"
#include "compassdata.h"
#include "compassprogram.h"

#include <glm/glm.hpp> // vec*, mat*

#include <memory> // shared_ptr

class Compass : public Object {
public:
    Compass(std::shared_ptr<Camera> modelingCamera);

    void setData(std::shared_ptr<CompassData> data);
    void setProgram(std::shared_ptr<CompassProgram> program);

    std::shared_ptr<CompassData> data() const;
    std::shared_ptr<CompassProgram> program() const;

    virtual glm::mat4 modelMatrix();
    virtual void render() override;

private:
    std::shared_ptr<Camera> m_modelingCamera;
    std::shared_ptr<CompassData> m_data;
    std::shared_ptr<CompassProgram> m_program;
};

#endif
