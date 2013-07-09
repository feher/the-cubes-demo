#ifndef COMPASS_LABEL_H
#define COMPASS_LABEL_H

#include "object.h"
#include "compasslabeldata.h"
#include "compasslabelprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class CompassLabel : public Object {
public:
    explicit CompassLabel(std::shared_ptr<Object> compass);

    void setData(std::shared_ptr<CompassLabelData> data);
    void setProgram(std::shared_ptr<CompassLabelProgram> program);

    virtual void render() override;

private:
    std::shared_ptr<CompassLabelData> m_data;
    std::shared_ptr<CompassLabelProgram> m_program;
    std::shared_ptr<Object> m_compass;
};

#endif
