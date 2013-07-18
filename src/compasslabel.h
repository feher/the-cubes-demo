#ifndef COMPASS_LABEL_H
#define COMPASS_LABEL_H

#include "object.h"
#include "compasslabeldata.h"
#include "objectprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class CompassLabel : public Object {
public:
    explicit CompassLabel(std::shared_ptr<Object> compass);

    void setData(std::shared_ptr<const CompassLabelData> data);
    void setProgram(std::shared_ptr<ObjectProgram<CompassLabel>> program);

    virtual void render() override;

    inline glm::mat4 programMvp();
    inline GLuint programTextureId() const;
    inline GLuint programVertexBufferId() const;
    inline GLuint programUvBufferId() const;
    inline void* programUvOffset() const;

private:
    enum {
        X_LABEL,
        Y_LABEL,
        Z_LABEL
    };

    std::shared_ptr<const CompassLabelData> m_data;
    std::shared_ptr<ObjectProgram<CompassLabel>> m_program;
    std::shared_ptr<Object> m_compass;
    int m_drawState;
};

glm::mat4 CompassLabel::programMvp() {
    // The V and P matrices are the identity matrices.
    return modelMatrix();
}

GLuint CompassLabel::programTextureId() const {
    return m_data->textureId();
}

GLuint CompassLabel::programVertexBufferId() const {
    return m_data->vertexBufferId();
}

GLuint CompassLabel::programUvBufferId() const {
    return m_data->uvBufferId();
}

void* CompassLabel::programUvOffset() const {
    return reinterpret_cast<void*>(m_drawState * sizeof(GLfloat) * 8);
}

#endif
