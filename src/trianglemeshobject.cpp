#include "trianglemeshobject.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

void TriangleMeshObject::setData(shared_ptr<TriangleMeshData> data) {
    m_data = data;
}
void TriangleMeshObject::setProgram(shared_ptr<LightTextureProgram> program) {
    m_program = program;
}

Geom::Sphere TriangleMeshObject::boundingSphere() const {
    return m_data->boundingSphere(position(), scale());
}

void TriangleMeshObject::updatePosition(const vec3& delta) {
    const auto& p3 = position();
    const auto& p = vec4(p3.x, p3.y, p3.z, 1);
    auto pc = camera()->viewMatrix() * p;
    pc.x = pc.x + delta.x;
    pc.y = pc.y + delta.y;
    pc.z = pc.z + delta.z;
    const auto& I = inverse(camera()->viewMatrix());
    const auto& pw = I * pc;
    setPosition(vec3(pw.x, pw.y, pw.z));
}

void TriangleMeshObject::render() {
    const auto& Mnoscale = unscaledModelMatrix();
    const auto& M = modelMatrix();
    const auto& V = camera()->viewMatrix();
    const auto& P = *projectionMatrix();
    const auto& MVP = P * V * M;

    m_program->activate();

    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(m_program->u_mId, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(m_program->u_vId, 1, GL_FALSE, &V[0][0]);
    glUniformMatrix4fv(m_program->u_mnsId, 1, GL_FALSE, &Mnoscale[0][0]);
    const auto& lightPos = light()->position();
    const auto& lightColor = light()->color();
    glUniform3fv(m_program->uw_lightPositionId, 1, &(lightPos[0]));
    glUniform3fv(m_program->u_lightColorId, 1, &(lightColor[0]));
    glUniform1f(m_program->u_lightPowerId, light()->power());
    auto highlightFactor =
                 (state() == HOVERED)
                 ? m_data->hoverHighlightFactor()
                 : 1.0f;
    glUniform1f(m_program->u_highlightFactorId, highlightFactor);
    const auto& ambient = m_data->materialAmbientFactor();
    const auto& specular = m_data->materialSpecularFactor();
    glUniform4fv(m_program->u_materialAmbientFactorId, 1, &ambient[0]);
    glUniform4fv(m_program->u_materialSpecularFactorId, 1, &specular[0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_data->textureId());
    glUniform1i(m_program->u_textureSamplerId, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBufferId());
    glEnableVertexAttribArray(m_program->am_vertexPositionId);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, position)));
    glEnableVertexAttribArray(m_program->am_vertexNormalId);
    glVertexAttribPointer(m_program->am_vertexNormalId, 3, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, normal)));
    glEnableVertexAttribArray(m_program->a_vertexUvId);
    glVertexAttribPointer(m_program->a_vertexUvId, 2, GL_FLOAT, GL_FALSE,
                          sizeof(TriangleMeshData::VertexData),
                          reinterpret_cast<void*>(offsetof(TriangleMeshData::VertexData, uv)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());

    viewport()->activate();

    glDrawElements(GL_TRIANGLES,
                   m_data->elementCount(),
                   GL_UNSIGNED_BYTE, nullptr);

    glDisableVertexAttribArray(m_program->am_vertexPositionId);
    glDisableVertexAttribArray(m_program->am_vertexNormalId);
    glDisableVertexAttribArray(m_program->a_vertexUvId);
}
