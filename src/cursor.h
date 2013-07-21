#ifndef CURSOR_H
#define CURSOR_H

#include "object.h"
#include "labeldata.h"
#include "objectprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class Cursor : public Object {
public:
    inline void setData(std::shared_ptr<const LabelData> data);
    inline void setProgram(std::shared_ptr<ObjectProgram<Cursor>> program);

    virtual void render() override;

    inline glm::mat4 programMvp();
    inline GLuint programTextureId() const;
    inline GLuint programVertexBufferId() const;
    inline GLuint programUvBufferId() const;
    inline void* programUvOffset() const;

private:
    std::shared_ptr<const LabelData> m_data;
    std::shared_ptr<ObjectProgram<Cursor>> m_program;
};

void Cursor::setData(std::shared_ptr<const LabelData> data) {
    m_data = data;
}

void Cursor::setProgram(std::shared_ptr<ObjectProgram<Cursor>> program) {
    m_program = program;
}

glm::mat4 Cursor::programMvp() {
    // The V and P matrices are the identity matrices.
    return modelMatrix();
}

GLuint Cursor::programTextureId() const {
    return m_data->textureId();
}

GLuint Cursor::programVertexBufferId() const {
    return m_data->vertexBufferId();
}

GLuint Cursor::programUvBufferId() const {
    return m_data->uvBufferId();
}

void* Cursor::programUvOffset() const {
    return nullptr;
}

#endif
