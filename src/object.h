#ifndef OBJECT_H
#define OBJECT_H

#include "geom.h"
#include "camera.h"
#include "objectdata.h"
#include "pointlight.h"
#include "viewport.h"

#include <glm/glm.hpp> // vec*, mat*
#include <GL/glew.h> // GLfloat

#include <memory> // shared_ptr

class Object {
public:
    enum {
        NONE,
        PRESSED,
        CLICKED,
        HOVERED,
        DISAPPEARING,
        APPEARING,
        DEAD
    };

    Object();
    virtual ~Object();

    void setId(int id);
    void setViewport(std::shared_ptr<const Viewport> viewPort);
    void setProjection(std::shared_ptr<glm::mat4> projectionMatrix);
    void setCamera(std::shared_ptr<Camera> camera);
    void setLight(std::shared_ptr<PointLight> light);
    void setRotation(glm::vec3 angle);
    void setScale(GLfloat scale);
    void setPosition(glm::vec3 position);
    void setColor(glm::vec4 color);
    void setInteractive(bool isInteractive);
    virtual void setState(unsigned int state);

    virtual void updatePosition(const glm::vec3& delta);

    int id() const;
    std::shared_ptr<const Viewport> viewport() const;
    std::shared_ptr<const glm::mat4> projectionMatrix() const;
    std::shared_ptr<const Camera> camera() const;
    std::shared_ptr<const PointLight> light() const;

    virtual glm::mat4 modelMatrix();
    const glm::mat4& unscaledModelMatrix();

    bool isInteractive() const;
    const glm::vec3& angle() const;
    GLfloat scale() const;
    const glm::vec3& position() const;
    const glm::vec4& color() const;
    unsigned int state() const;
    
    virtual Geom::Sphere boundingSphere() const;
    virtual void update(double deltaTime);
    virtual void render();

private:
    virtual glm::mat4 calculateModelMatrix(bool withScaling) const;

    int m_id;
    std::shared_ptr<const Viewport> m_viewport;
    std::shared_ptr<glm::mat4> m_projectionMatrix;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<PointLight> m_light;
    bool m_isModelMatrixValid;
    bool m_isUnscaledModelMatrixValid;
    bool m_isInteractive;
    glm::vec3 m_angle; // Rotation angles around the 3 axes.
    GLfloat m_scale;
    glm::vec3 m_position;
    glm::vec4 m_color;
    unsigned int m_state;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_unscaledModelMatrix;
};

#endif
