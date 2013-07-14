#include "trianglemeshobject.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

void TriangleMeshObject::setData(shared_ptr<TriangleMeshData> data) {
    m_data = data;
}

void TriangleMeshObject::setProgram(shared_ptr<ObjectProgram<TriangleMeshObject>> program) {
    m_program = program;
}

shared_ptr<ObjectProgram<TriangleMeshObject>>
TriangleMeshObject::program() const {
    return m_program;
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

void TriangleMeshObject::initRender() {
    m_program->activate();
    m_program->configure(*this);
    viewport()->activate();
}

void TriangleMeshObject::finishRender() {
    m_program->cleanup();
}

void TriangleMeshObject::render() {
    initRender();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->elementBufferId());
    glDrawElements(GL_TRIANGLES,
                   m_data->elementCount(),
                   GL_UNSIGNED_BYTE, nullptr);
    finishRender();
}
