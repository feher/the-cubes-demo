#ifndef TRIANGLE_MESH_OBJECT_H
#define TRIANGLE_MESH_OBJECT_H

#include "object.h"
#include "trianglemeshdata.h"
#include "objectprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class TriangleMeshObject : public Object {
public:
    void setData(std::shared_ptr<TriangleMeshData> data);
    void setProgram(std::shared_ptr<ObjectProgram<TriangleMeshObject>> program);

    std::shared_ptr<ObjectProgram<TriangleMeshObject>> program() const;

    virtual Geom::Sphere boundingSphere() const;
    virtual void updatePosition(const glm::vec3& delta) override;
    virtual void render() override;

    inline glm::mat4 programMvp();
    inline glm::mat4 programModelMatrix();
    inline const glm::mat4& programUnscaledModelMatrix();
    inline const glm::mat4& programViewMatrix() const;
    inline const glm::vec3& programLightPos() const;
    inline const glm::vec3& programLightColor() const;
    inline GLfloat programLightPower() const;
    inline GLfloat programHighlightFactor() const;
    inline const glm::vec3& programMaterialAmbientFactor() const;
    inline const glm::vec3& programMaterialSpecularFactor() const;
    inline GLuint programTextureId() const;
    inline GLuint programVertexBufferId() const;

private:
    virtual void initRender();
    virtual void finishRender();

    std::shared_ptr<TriangleMeshData> m_data;
    std::shared_ptr<ObjectProgram<TriangleMeshObject>> m_program;
};

glm::mat4 TriangleMeshObject::programMvp() {
    const auto& M = modelMatrix();
    const auto& V = camera()->viewMatrix();
    const auto& P = *projectionMatrix();
    const auto& MVP = P * V * M;
    return MVP;
}

glm::mat4 TriangleMeshObject::programModelMatrix() {
    return modelMatrix();
}

const glm::mat4& TriangleMeshObject::programUnscaledModelMatrix() {
    return unscaledModelMatrix();
}

const glm::mat4& TriangleMeshObject::programViewMatrix() const {
    return camera()->viewMatrix();
}

const glm::vec3& TriangleMeshObject::programLightPos() const {
    return light()->position();
}

const glm::vec3& TriangleMeshObject::programLightColor() const {
    return light()->color();
}

GLfloat TriangleMeshObject::programLightPower() const {
    return light()->power();
}

GLfloat TriangleMeshObject::programHighlightFactor() const {
    return (state() == HOVERED)
           ? m_data->hoverHighlightFactor()
           : 1.0f;
}

const glm::vec3& TriangleMeshObject::programMaterialAmbientFactor() const {
    return m_data->materialAmbientFactor();
}

const glm::vec3& TriangleMeshObject::programMaterialSpecularFactor() const {
    return m_data->materialSpecularFactor();
}

GLuint TriangleMeshObject::programTextureId() const {
    return m_data->textureId();
}

GLuint TriangleMeshObject::programVertexBufferId() const {
    return m_data->vertexBufferId();
}

#endif
