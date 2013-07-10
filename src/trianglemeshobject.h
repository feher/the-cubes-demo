#ifndef TRIANGLE_MESH_OBJECT_H
#define TRIANGLE_MESH_OBJECT_H

#include "object.h"
#include "trianglemeshdata.h"
#include "lighttextureprogram.h"

#include <glm/glm.hpp> // vec*, mat*

class TriangleMeshObject : public Object {
public:
    void setData(std::shared_ptr<TriangleMeshData> data);
    void setProgram(std::shared_ptr<LightTextureProgram> program);

    virtual Geom::Sphere boundingSphere() const;
    virtual void updatePosition(const glm::vec3& delta) override;
    virtual void render() override;

private:
    std::shared_ptr<TriangleMeshData> m_data;
    std::shared_ptr<LightTextureProgram> m_program;
};

#endif
