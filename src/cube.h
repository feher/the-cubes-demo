#ifndef CUBE_H
#define CUBE_H

#include "object.h"
#include "cubedata.h"
#include "cubeprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class Cube : public Object {
public:
    void setData(std::shared_ptr<CubeData> data);
    void setProgram(std::shared_ptr<CubeProgram> program);

    std::shared_ptr<CubeData> data() const;
    std::shared_ptr<CubeProgram> program() const;

    virtual void updatePosition(const glm::vec3& delta) override;
    virtual void render() override;

private:
    virtual GLuint uvBufferId() const = 0;
    virtual GLuint textureId() const = 0;

    std::shared_ptr<CubeData> m_data;
    std::shared_ptr<CubeProgram> m_program;
};

#endif
