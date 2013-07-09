#ifndef THE_CUBES_H
#define THE_CUBES_H

#include "rglfw.h"
#include "camera.h"
#include "object.h"
#include "pointlight.h"
#include "viewport.h"
#include "cubedata.h"
#include "cubeprogram.h"
#include "griddata.h"
#include "gridprogram.h"
#include "compassdata.h"
#include "compasslabeldata.h"
#include "compasslabelprogram.h"

#include <glm/glm.hpp> // vec2, mat4

#include <memory>    // shared_ptr
#include <vector>
#include <random> // mt19937, uniform_int_distribution

class TheCubes {
public:
    explicit TheCubes(unsigned int screenWidth, unsigned int screenHeight);

    void run();

private:
    enum {
        MOVING_OBJECT, MOVING_CAMERA, NONE
    };

    void createNewObject();
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
    bool m_isMouseButtonPressed;
    bool m_isMouseMoved;
    glm::vec2 m_lastMousePos;
    unsigned int m_inputState;
    std::default_random_engine m_randEngine;
    std::uniform_int_distribution<int> m_uniformDist;
    std::shared_ptr<Viewport> m_modelingViewport;
    std::shared_ptr<glm::mat4> m_modelingProjection;
    std::shared_ptr<Camera> m_modelingCamera;
    std::shared_ptr<PointLight> m_modelingLight;
    std::shared_ptr<Object> m_actionCube;
    std::shared_ptr<Object> m_movingObject;
    std::shared_ptr<CubeData> m_cubeData;
    std::shared_ptr<CubeProgram> m_cubeProgram;
    std::vector<std::shared_ptr<CubeData>> m_cubeDatas;
    std::vector<std::shared_ptr<Viewport>> m_viewports;
    std::vector<std::shared_ptr<glm::mat4>> m_projections;
    std::vector<std::shared_ptr<Camera>> m_cameras;
    std::vector<std::shared_ptr<PointLight>> m_lights;
    std::vector<std::shared_ptr<Object>> m_hudObjects;
    std::vector<std::shared_ptr<Object>> m_modelingObjects;
    std::vector<std::shared_ptr<Object>> m_modelObjects;
    std::vector<std::shared_ptr<Object>> m_interactiveObjects;
};

#endif
