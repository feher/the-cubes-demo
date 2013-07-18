#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include "trianglemeshobject.h"
#include "shadowmap.h"

#include <GL/glew.h> // GL*

class ModelObject : public TriangleMeshObject {
public:
    explicit ModelObject(GLfloat scale);

    inline void setProgram(std::shared_ptr<ObjectProgram<ModelObject>> program);
    inline void setProgram(std::shared_ptr<ObjectProgram<TriangleMeshObject>> program);
    inline void setShadowMap(std::shared_ptr<const ShadowMap> shadowMap);

    inline std::shared_ptr<ObjectProgram<ModelObject>> modelProgram();

    virtual void update(double deltaTime) override;

    inline glm::mat4 programShadowMvp();
    inline GLuint programShadowTextureId() const;
    inline glm::vec3 programDirectionalLightDirection() const;

private:
    virtual void initRender() override;
    virtual void finishRender() override;

    GLfloat m_pulse;
    GLfloat m_originalScale;
    GLfloat m_rotationSpeedOffset;
    std::shared_ptr<const ShadowMap> m_shadowMap;
    std::shared_ptr<ObjectProgram<ModelObject>> m_modelProgram;
};

void ModelObject::setProgram(std::shared_ptr<ObjectProgram<ModelObject>> program) {
    m_modelProgram = program;
}

void ModelObject::setProgram(std::shared_ptr<ObjectProgram<TriangleMeshObject>> program) {
    m_modelProgram = nullptr;
    TriangleMeshObject::setProgram(program);
}

void ModelObject::setShadowMap(std::shared_ptr<const ShadowMap> shadowMap) {
    m_shadowMap = shadowMap;
}

std::shared_ptr<ObjectProgram<ModelObject>> ModelObject::modelProgram() {
    return m_modelProgram;
}

glm::mat4 ModelObject::programShadowMvp() {
    assert(m_shadowMap);
    return m_shadowMap->vp() * modelMatrix();
}

GLuint ModelObject::programShadowTextureId() const {
    assert(m_shadowMap);
    return m_shadowMap->shadowTextureId();
}

glm::vec3 ModelObject::programDirectionalLightDirection() const {
    assert(m_shadowMap);
    return glm::normalize(m_shadowMap->lightDirection());
}

#endif
