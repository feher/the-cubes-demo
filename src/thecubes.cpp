
#include "thecubes.h"

#include "actionobject.h"
#include "modelobject.h"
#include "grid.h"
#include "compass.h"
#include "compasslabel.h"
#include "griddata.h"
#include "gridprogram.h"
#include "compassdata.h"
#include "compassprogram.h"
#include "compasslabeldata.h"
#include "compasslabelprogram.h"
#include "lighttextureprogram.h"
#include "lighttextureshadowprogram.h"
#include "shadowmapprogram.h"
#include "shadowmapviewprogram.h"
#include "cubedata.h"
#include "spheredata.h"
#include "frametimer.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h> // GL*
#include <GL/glfw.h> // glfw*

#include <limits> // numeric_limits
#include <iostream>

using namespace std;
using namespace glm;

enum {
    NO_INPUT = 0,
    SHIFT_PRESSED = 1 << 0,
    CTRL_PRESSED = 1 << 1,
    ALT_PRESSED = 1 << 2,
    S_PRESSED = 1 << 3,
    D_PRESSED = 1 << 4,
    MOUSE_PRESS_STARTED = 1 << 5,
    MOUSE_CLICKED = 1 << 6,
    MOUSE_MOVED = 1 << 7,
    MOUSE_POS_VALID = 1 << 8,
    MOUSE_PRESSED = 1 << 9,
};

enum {
    MOVING_OBJECT, MOVING_CAMERA, NO_STATE
};

TheCubes::TheCubes(unsigned int screenWidth, unsigned int screenHeight)
    : m_screenWidth(screenWidth),
      m_screenHeight(screenHeight),
      m_lastTime(0),
      m_exitting(false),
      m_isShadowMapEnabled(false),
      m_isShadowMapViewEnabled(false),
      m_wasSDown(false),
      m_wasDDown(false),
      m_isMouseButtonPressed(false),
      m_lastMousePos(0, 0),
      m_inputState(NO_STATE) {
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

    if (!glfwOpenWindow(screenWidth, screenHeight, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        throw runtime_error("Cannot create window");
    }

    if (glewInit() != GLEW_OK) {
        throw runtime_error("Cannot init GLEW");
    }

    glfwSetWindowTitle("The Cubes");
    glfwSetMousePos(m_screenWidth / 2, m_screenHeight / 2);
    glfwEnable(GLFW_MOUSE_CURSOR);
    glfwEnable(GLFW_STICKY_KEYS);

    const float bgColor = 0.3f;
    glClearColor(bgColor, bgColor, bgColor, 0.0f);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    m_vaoId.generate(GlBuffer::VAO);
    glBindVertexArray(m_vaoId.id());

    m_lightTextureShadowProgram = make_shared<LightTextureShadowProgram>();
    m_lightTextureProgram = make_shared<LightTextureProgram>();
    auto gridProgram = make_shared<GridProgram>();

    m_modelCubeData = make_shared<CubeData>(CubeData::modelTextureFile,
                                            CubeData::modelNormalFile);
    m_modelSphereData = make_shared<SphereData>(SphereData::modelTextureFile,
                                                SphereData::modelNormalFile);

    // Set up the modeling scene
    {
        auto viewport = make_shared<Viewport>(0, 0, m_screenWidth, m_screenHeight);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0, 15, 15), vec3(180, -50, 0));
        auto light = make_shared<PointLight>(camera->position(), vec3(1, 1, 1), 100.0f);
        light->linkToCamera(camera);

        auto grid = make_shared<Grid>();
        grid->setData(make_shared<GridData>());
        grid->setProgram(gridProgram);
        grid->setViewport(viewport);
        grid->setProjection(projection);
        grid->setCamera(camera);
        grid->setLight(light);
        grid->setRotation(vec3(0, 0, 0));
        grid->setScale(1.0f);
        grid->setPosition(vec3(0, 0, 0));
        grid->setColor(vec4(0.4f, 0.4f, 0.4f, 1));
        grid->setState(Object::NONE);
        grid->setInteractive(false);

        m_viewports.push_back(viewport);
        m_projections.push_back(projection);
        m_cameras.push_back(camera);
        m_lights.push_back(light);
        m_modelingObjects.push_back(grid);

        m_modelingViewport = viewport;
        m_modelingProjection = projection;
        m_modelingCamera = camera;
        m_modelingLight = light;
    }

    // Set up the action cube scene
    {
        auto viewport = make_shared<Viewport>(0, 0, m_screenWidth / 5, m_screenHeight / 5);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0, 2, 5), vec3(180, -30, -5));
        auto light = make_shared<PointLight>(vec3(0, 1, 10), vec3(1, 1, 1), 100.0f);
        auto cube = make_shared<ActionObject>(1.0f);
        cube->setData(
            make_shared<CubeData>(CubeData::actionTextureFile, CubeData::actionNormalFile));
        cube->setProgram(m_lightTextureProgram);
        cube->setViewport(viewport);
        cube->setProjection(projection);
        cube->setCamera(camera);
        cube->setLight(light);
        cube->setRotation(vec3(0, 0, 0));
        cube->setScale(1.0f);
        cube->setPosition(vec3(0, 0, 0));
        cube->setColor(vec4(0, 0, 1, 1));
        cube->setState(Object::NONE);
        cube->setInteractive(true);

        m_viewports.push_back(viewport);
        m_projections.push_back(projection);
        m_cameras.push_back(camera);
        m_lights.push_back(light);
        m_hudObjects.push_back(cube);
        m_interactiveObjects.push_back(cube);

        m_actionCube = cube;
    }

    // Set up the action sphere scene
    {
        auto viewport = make_shared<Viewport>(0, m_screenHeight - (m_screenHeight / 4),
                                              m_screenWidth / 5, m_screenHeight / 5);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0.2f, 1.7, 3.5), vec3(180, -25, -5));
        auto light = make_shared<PointLight>(vec3(0, 1, 9), vec3(1, 1, 1), 80.0f);
        auto sphere = make_shared<ActionObject>(1.0f);
        sphere->setData(
            make_shared<SphereData>(SphereData::actionTextureFile, SphereData::actionNormalFile));
        sphere->setProgram(m_lightTextureProgram);
        sphere->setViewport(viewport);
        sphere->setProjection(projection);
        sphere->setCamera(camera);
        sphere->setLight(light);
        sphere->setRotation(vec3(0, 0, 0));
        sphere->setScale(1.0f);
        sphere->setPosition(vec3(0, 0, 0));
        sphere->setColor(vec4(0, 0, 1, 1));
        sphere->setState(Object::NONE);
        sphere->setInteractive(true);

        m_viewports.push_back(viewport);
        m_projections.push_back(projection);
        m_cameras.push_back(camera);
        m_lights.push_back(light);
        m_hudObjects.push_back(sphere);
        m_interactiveObjects.push_back(sphere);

        m_actionSphere = sphere;
    }

    // Set up the compass scene
    {
        auto viewport = make_shared<Viewport>(
            m_screenWidth - (m_screenWidth / 6), 0,
            m_screenHeight / 6, m_screenHeight / 6);
        auto projection = make_shared<mat4>(ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0));
        auto camera = make_shared<Camera>(vec3(0, 0, 0), vec3(180, 0, 0));
        auto light = make_shared<PointLight>(camera->position(), vec3(1, 1, 1), 0.0f);
        auto compass = make_shared<Compass>(m_modelingCamera);
        compass->setData(make_shared<CompassData>());
        compass->setProgram(make_shared<CompassProgram>());
        compass->setViewport(viewport);
        compass->setProjection(projection);
        compass->setCamera(camera);
        compass->setLight(light);
        compass->setRotation(vec3(0, 0, 0));
        compass->setScale(2.3f);
        compass->setPosition(vec3(0, 0, 0));
        compass->setColor(vec4(0, 0, 1, 1));
        compass->setState(Object::NONE);
        compass->setInteractive(false);

        auto label = make_shared<CompassLabel>(compass);
        label->setData(make_shared<CompassLabelData>());
        label->setProgram(make_shared<CompassLabelProgram>());
        label->setViewport(viewport);
        label->setProjection(projection);
        label->setCamera(camera);
        label->setLight(light);
        label->setRotation(vec3(0, 0, 0));
        label->setScale(0.2f);
        label->setPosition(vec3(0, 0, 0));
        label->setColor(vec4(0, 0, 1, 1));
        label->setState(Object::NONE);
        label->setInteractive(false);

        m_viewports.push_back(viewport);
        m_projections.push_back(projection);
        m_cameras.push_back(camera);
        m_lights.push_back(light);
        m_hudObjects.push_back(compass);
        m_hudObjects.push_back(label);
    }

    // Initialize shadow mapping related objects.
    m_shadowMap = make_shared<ShadowMap>(vec3(0.0f, 0.0f, -1.0f));
    m_shadowMap->setScreenViewport(m_modelingViewport);
    m_shadowMap->linkToCamera(m_modelingCamera);
    m_shadowMapProgram = make_shared<ShadowMapProgram>();
    m_shadowMapView = make_shared<ShadowMapView>();
    m_shadowMapView->setProgram(make_shared<ShadowMapViewProgram>());
    m_shadowMapView->setShadowMap(m_shadowMap);
    m_shadowMapView->setViewport(
        make_shared<Viewport>(m_screenWidth - 256, m_screenHeight - 256, 256, 256));

    // Add a few initial models.
    createNewObject(m_actionCube, vec3(+2, -1.5, 15));
    createNewObject(m_actionSphere, vec3(1.0, 2.3, 12));
    createNewObject(m_actionSphere, vec3(-2, -2, 10));
    createNewObject(m_actionCube, vec3(-2.3, +1.5, 10));
}

void TheCubes::updateAndRender() {
    const double currentTime = glfwGetTime();
    const float deltaTime = float(currentTime - m_lastTime);
    m_lastTime = currentTime;

    for (auto& object : m_modelObjects) {
        object->update(deltaTime);
    }

    if (m_isShadowMapEnabled) {
        // Render to shadow map
        m_shadowMap->activate();
        for (auto& object : m_modelObjects) {
            const auto originalProgram = object->modelProgram();
            const auto originalViewport = object->viewport();
            object->setViewport(m_shadowMap->viewport());
            object->setProgram(m_shadowMapProgram);
            object->render();
            object->setViewport(originalViewport);
            object->setProgram(originalProgram);
        }
        m_shadowMap->cleanup();
    }

    // Render to screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto& object : m_modelingObjects) {
        object->render();
    }
    for (auto& object : m_hudObjects) {
        object->update(deltaTime);
        object->render();
    }
    if (m_isShadowMapViewEnabled) {
        m_shadowMapView->render();
    }

    glfwSwapBuffers();
}

void TheCubes::createNewObject(const shared_ptr<const Object>& actionObject,
                               const vec3& positionInCamera) {
    bool isCube = (actionObject == m_actionCube);

    auto object = make_shared<ModelObject>(1.0f);

    if (isCube) {
        object->setData(m_modelCubeData);
    } else {
        object->setData(m_modelSphereData);
    }

    if (m_isShadowMapEnabled) {
        object->setProgram(m_lightTextureShadowProgram);
    } else {
        object->setProgram(m_lightTextureProgram);
    }

    object->setId(m_modelingObjects.size());
    object->setViewport(m_modelingViewport);
    object->setProjection(m_modelingProjection);
    object->setCamera(m_modelingCamera);
    object->setLight(m_modelingLight);
    object->setShadowMap(m_shadowMap);
    object->setRotation(positionInCamera * 40.0f);
    object->setScale(1.0f);

    const auto& cameraBase = m_modelingCamera->base();
    const auto& pw = (cameraBase * positionInCamera) + m_modelingCamera->position();
    object->setPosition(pw);

    object->setColor(vec4(0, 1, 0, 1));
    object->setState(Object::APPEARING);
    object->setInteractive(true);

    m_modelObjects.push_back(object);
    m_modelingObjects.push_back(object);
    m_interactiveObjects.push_back(object);

    m_exitting = false;
}

void TheCubes::setShadowMapEnabled(bool isEnabled) {
    m_isShadowMapEnabled = isEnabled;
    for (auto& object : m_modelObjects) {
        if (m_isShadowMapEnabled) {
            object->setProgram(m_lightTextureShadowProgram);
        } else {
            object->setProgram(m_lightTextureProgram);
        }
    }
}

bool TheCubes::isActionObject(const shared_ptr<const Object>& object) const {
    return object == m_actionCube || object == m_actionSphere;
}

shared_ptr<Object> TheCubes::selectedObject(const vec2& mousePos) const {
    auto selection = shared_ptr<Object>();
    auto closestDistance = numeric_limits<float>::max();
    const Viewport* viewport = nullptr;
    const Camera* camera = nullptr;
    const mat4* projectionMatrix = nullptr;
    auto ray = Geom::Ray(vec4(0.0f), vec4(0.0f));

    for (auto& object : m_interactiveObjects) {
        if (!object->isInteractive()
            || object->state() == Object::DEAD) {
            continue;
        }
        if (viewport != object->viewport().get()
            || camera != object->camera().get()
            || projectionMatrix != object->projectionMatrix().get()) {
            // Calculate the ray coordinates only if necessary.
            auto vpx = object->viewport()->x;
            auto vpy = object->viewport()->y;
            auto vpw = object->viewport()->width;
            auto vph = object->viewport()->height;
            // The mouse position is in physical screen dimensions.
            // The mouse position's Y axis points down, but the viewport's Y axis
            // points up. So we must invert it.
            // vpp = mouse poistion in the viewport coordinate system.
            const auto& vpp = vec2(mousePos.x - vpx, m_screenHeight - mousePos.y - vpy);
            if (vpp.x < 0 || vpp.x >= vpw || vpp.y < 0 || vpp.y >= vph) {
                // The vpp (viewport position) falls outside of the viewport.
                continue;
            }
            ray = Geom::World::ray(vec2(vpw, vph), vpp,
                                   object->camera()->viewMatrix(),
                                   *(object->projectionMatrix()));
            viewport = object->viewport().get();
            camera = object->camera().get();
            projectionMatrix = object->projectionMatrix().get();
        }

        const auto& sphere = object->boundingSphere();
        const auto& intersections = Geom::World::intersect(ray, sphere);
        if (!intersections.empty()) {
            if (isActionObject(object)) {
                // These objects are on top of everything.
                selection = object;
                break;
            } else {
                const auto& i1 = intersections[0];
                const auto& i2 = intersections[1];
                float d = (i1.t > 0)
                          ? glm::distance(ray.origin, i1.p)
                          : (i2.t > 0)
                          ? glm::distance(ray.origin, i2.p)
                          : numeric_limits<float>::max();
                if (closestDistance > d) {
                    selection = object;
                    closestDistance = d;
                }
            }
        }
    }

    return selection;
}

void TheCubes::clearHoveredState() {
    for (auto& object : m_interactiveObjects) {
        if (object->state() == Object::HOVERED) {
            object->setState(Object::NONE);
        }
    }
}

int TheCubes::inputFlags(vec2& mousePosDelta) {
    int flags = NO_INPUT;

    auto isSDown = (glfwGetKey('S') == GLFW_PRESS);
    auto isDDown = (glfwGetKey('D') == GLFW_PRESS);
    auto mousePos = vec2(-1, -1);
    auto delta = vec2(0, 0);

    flags |= SHIFT_PRESSED * (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS);
    flags |= CTRL_PRESSED * (glfwGetKey(GLFW_KEY_LCTRL) == GLFW_PRESS);
    flags |= ALT_PRESSED * (glfwGetKey(GLFW_KEY_LALT) == GLFW_PRESS);

    if (m_wasSDown && !isSDown) {
        m_wasSDown = false;
        flags |= S_PRESSED;
    }
    m_wasSDown = isSDown;

    if (m_wasDDown && !isDDown) {
        m_wasDDown = false;
        flags |= D_PRESSED;
    }
    m_wasDDown = isDDown;

    int mx, my;
    glfwGetMousePos(&mx, &my);
    mousePos = vec2(mx, my);
    delta = mousePos - m_lastMousePos;
    if (0 <= mx && mx < int(m_screenWidth)
        && 0 <= my && my < int(m_screenHeight)) {
        flags |= MOUSE_POS_VALID;
        if (m_lastMousePos != mousePos) {
            flags |= MOUSE_MOVED;
            m_lastMousePos = mousePos;
        }
    }

    auto mouseButtonState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    if (mouseButtonState == GLFW_PRESS) {
        flags |= MOUSE_PRESSED;
        if (!m_isMouseButtonPressed) {
            m_isMouseButtonPressed = true;
            flags |= MOUSE_PRESS_STARTED;
        }
    }
    if (mouseButtonState == GLFW_RELEASE && m_isMouseButtonPressed) {
        // Mouse button was pressed and then released.
        m_isMouseButtonPressed = false;
        flags |= MOUSE_CLICKED;
    }

    mousePosDelta = delta;
    return flags;
}

void TheCubes::handleInput() {
    auto delta = vec2(0.0f);
    auto flags = inputFlags(delta);

    switch (m_inputState) {
    case NO_STATE:
        switch (flags) {
        case (MOUSE_POS_VALID | MOUSE_CLICKED) : {
                // Clicked on object (press + release, not just press)
                auto object = selectedObject(m_lastMousePos);
                if (object && !isActionObject(object)
                    && (object->state() == Object::HOVERED || object->state() == Object::NONE)) {
                    object->setState(Object::DISAPPEARING);
                }
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | MOUSE_PRESSED) : {
                auto object = selectedObject(m_lastMousePos);
                if (object && !isActionObject(object)) {
                    // Move object along Camera's (X, Y) plane.
                    m_movingObject = object;
                    m_inputState = MOVING_OBJECT;
                } else {
                    // Move camera on (X, Y) plane.
                    m_inputState = MOVING_CAMERA;
                }
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | MOUSE_PRESSED | CTRL_PRESSED) : {
                auto object = selectedObject(m_lastMousePos);
                if (object && !isActionObject(object)) {
                    // Move object along Camera's Z axis.
                    m_movingObject = object;
                    m_inputState = MOVING_OBJECT;
                }
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED) : {
                // Hovering over objects.
                clearHoveredState();
                auto object = selectedObject(m_lastMousePos);
                if (object && object->state() == Object::NONE) {
                    object->setState(Object::HOVERED);
                }
            }
            break;
        case (MOUSE_POS_VALID | MOUSE_PRESSED | MOUSE_PRESS_STARTED) : {
                // Create new object.
                auto object = selectedObject(m_lastMousePos);
                if (isActionObject(object)
                    && (object->state() == Object::NONE || object->state() == Object::HOVERED)) {
                    object->setState(Object::PRESSED);
                    createNewObject(object, vec3(0, 0, 10));
                }
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | SHIFT_PRESSED) : {
                // Pitch / Yaw camera
                const auto f = 0.1f;
                m_modelingCamera->updateAngles(vec3(delta.x * f, -delta.y * f, 0));
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | ALT_PRESSED) : {
                // Roll camera
                const auto f = 0.1f;
                m_modelingCamera->updateAngles(vec3(0, 0, -delta.y * f));
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | CTRL_PRESSED) : {
                // Move camera along Z axis
                const auto f = 0.1f;
                m_modelingCamera->updatePosition(vec3(0, 0, -delta.y * f));
            } break;
        case (MOUSE_POS_VALID | S_PRESSED) :
            setShadowMapEnabled(!m_isShadowMapEnabled);
            break;
        case (MOUSE_POS_VALID | D_PRESSED) :
            m_isShadowMapViewEnabled = !m_isShadowMapViewEnabled;
            break;
        default:
            break;
        } // switch inputFlags
        break;
    case MOVING_OBJECT:
        switch (flags) {
        case (MOUSE_POS_VALID | MOUSE_MOVED | MOUSE_PRESSED) : {
                // Move object along Camera's (X, Y) plane.
                const auto f = 0.01f;
                m_movingObject->updatePosition(vec3(delta.x * f, -delta.y * f, 0.0f));
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED | MOUSE_PRESSED | CTRL_PRESSED) : {
                // Move object along Camera's Z axis.
                const auto f = 0.05f;
                m_movingObject->updatePosition(vec3(0.0f, 0.0f, delta.y * f));
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED) :
        case (MOUSE_POS_VALID) :
            // Stop moving object.
            m_movingObject = nullptr;
            m_inputState = NO_STATE;
            break;
        default:
            break;
        }
        break;
    case MOVING_CAMERA:
        switch (flags) {
        case (MOUSE_POS_VALID | MOUSE_MOVED | MOUSE_PRESSED) : {
                // Move camera along (X, Y) plane.
                const auto f = 0.01f;
                m_modelingCamera->updatePosition(vec3(delta.x * f, delta.y * f, 0));
            } break;
        case (MOUSE_POS_VALID | MOUSE_MOVED) :
        case (MOUSE_POS_VALID) :
            // Stop moving camera.
            m_inputState = NO_STATE;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void TheCubes::killModelObjects() {
    for (auto& object : m_modelObjects) {
        object->setState(Object::DISAPPEARING);
    }
}

void TheCubes::cleanupDeadModelObjects() {
    vector<shared_ptr<ModelObject>> clean;
    for (auto& object : m_modelObjects) {
        if (object->state() != Object::DEAD) {
            clean.push_back(object);
        }
    }
    m_modelObjects = clean;
}

void TheCubes::run() {
    m_exitting = false;
    m_lastTime = glfwGetTime();
    auto frameTimer = FrameTimer();
    do {
        updateAndRender();
        handleInput();
        cleanupDeadModelObjects();
        if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS
             || (!glfwGetWindowParam(GLFW_OPENED))) {
            killModelObjects();
            m_exitting = true;
        }
        frameTimer.tickAndPrint(cout);
    } while (!m_exitting || !m_modelObjects.empty());
}
