#ifndef GRID_H
#define GRID_H

#include "object.h"
#include "griddata.h"
#include "objectprogram.h"

class Grid : public Object {
public:
    void setData(std::shared_ptr<GridData> data);
    void setProgram(std::shared_ptr<ObjectProgram<Grid>> program);

    virtual void render() override;

    inline const glm::vec4& programColor() const;
    inline glm::mat4 programMvp();
    inline GLuint programVertexBufferId() const;

private:
    std::shared_ptr<GridData> m_data;
    std::shared_ptr<ObjectProgram<Grid>> m_program;
};

const glm::vec4& Grid::programColor() const {
    return color();
}

glm::mat4 Grid::programMvp() {
    const auto& M = modelMatrix();
    const auto& V = camera()->viewMatrix();
    const auto& P = *projectionMatrix();
    return (P * V * M);
}

GLuint Grid::programVertexBufferId() const {
    return m_data->vertexBufferId();
}

#endif
