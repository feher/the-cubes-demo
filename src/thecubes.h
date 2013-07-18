#ifndef THE_CUBES_H
#define THE_CUBES_H

#include "rglfw.h"
#include "camera.h"
#include "object.h"
#include "trianglemeshobject.h"
#include "modelobject.h"
#include "pointlight.h"
#include "viewport.h"
#include "shadowmap.h"
#include "shadowmapview.h"
#include "cubedata.h"
#include "spheredata.h"
#include "glbuffer.h"

#include <glm/glm.hpp> // vec2, mat4

#include <memory>    // shared_ptr, unique_ptr
#include <vector>

class TheCubes {
public:
    explicit TheCubes(unsigned int screenWidth, unsigned int screenHeight);

    void run();

private:
    enum {
        MOVING_OBJECT, MOVING_CAMERA, NONE
    };

    void createNewObject(const std::shared_ptr<const Object>& actionObject,
                         const glm::vec3& positionInCamera);
    void setShadowMapEnabled(bool isEnabled);
    bool isActionObject(const std::shared_ptr<const Object>& object) const;
    std::shared_ptr<Object> selectedObject(const glm::vec2& mousePos) const;
    void clearHoveredState();
    void handleInput();
    void updateAndRender();
    void killModelObjects();
    void cleanupDeadModelObjects();

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
    RGlfw m_glfw;
    double m_lastTime;
    bool m_exitting;
    bool m_isShadowMapEnabled;
    bool m_isShadowMapViewEnabled;
    bool m_wasSDown;
    bool m_wasDDown;
    bool m_isMouseButtonPressed;
    bool m_isMouseMoved;
    glm::vec2 m_lastMousePos;
    unsigned int m_inputState;
    GlBuffer m_vaoId;
    std::shared_ptr<ShadowMap> m_shadowMap;
    std::shared_ptr<Viewport> m_modelingViewport;
    std::shared_ptr<glm::mat4> m_modelingProjection;
    std::shared_ptr<Camera> m_modelingCamera;
    std::shared_ptr<PointLight> m_modelingLight;
    std::shared_ptr<Object> m_actionCube;
    std::shared_ptr<Object> m_actionSphere;
    std::shared_ptr<Object> m_movingObject;
    std::shared_ptr<ShadowMapView> m_shadowMapView;
    std::shared_ptr<ObjectProgram<TriangleMeshObject>> m_lightTextureProgram;
    std::shared_ptr<ObjectProgram<ModelObject>> m_lightTextureShadowProgram;
    std::shared_ptr<ObjectProgram<ModelObject>> m_shadowMapProgram;
    std::shared_ptr<CubeData> m_modelCubeData;
    std::shared_ptr<SphereData> m_modelSphereData;
    std::vector<std::shared_ptr<Viewport>> m_viewports;
    std::vector<std::shared_ptr<glm::mat4>> m_projections;
    std::vector<std::shared_ptr<Camera>> m_cameras;
    std::vector<std::shared_ptr<PointLight>> m_lights;
    std::vector<std::shared_ptr<Object>> m_hudObjects;
    std::vector<std::shared_ptr<Object>> m_modelingObjects;
    std::vector<std::shared_ptr<ModelObject>> m_modelObjects;
    std::vector<std::shared_ptr<Object>> m_interactiveObjects;
};

#endif
