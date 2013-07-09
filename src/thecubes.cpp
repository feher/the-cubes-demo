
#include "thecubes.h"

#include "actioncube.h"
#include "modelcube.h"
#include "grid.h"
#include "compass.h"
#include "compasslabel.h"
#include "griddata.h"
#include "gridprogram.h"
#include "compassdata.h"
#include "compassprogram.h"
#include "compasslabeldata.h"
#include "compasslabelprogram.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h> // GL*
#include <GL/glfw.h> // glfw*

#include <limits> // numeric_limits

using namespace std;
using namespace glm;

TheCubes::TheCubes(unsigned int screenWidth, unsigned int screenHeight)
    : m_screenWidth(screenWidth),
      m_screenHeight(screenHeight),
      m_lastTime(0),
      m_isMouseButtonPressed(false),
      m_isMouseMoved(false),
      m_lastMousePos(0, 0),
      m_inputState(NONE),
      m_uniformDist(0, 2000) {
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

    std::random_device rd;
    m_randEngine.seed(rd());

    m_cubeData = make_shared<CubeData>();
    m_cubeProgram = make_shared<CubeProgram>();
    auto gridProgram = make_shared<GridProgram>();

    // Set up the modeling scene
    {
        auto viewport = make_shared<Viewport>(0, 0, m_screenWidth, m_screenHeight);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0, 15, 15), vec3(180, -50, 0));
        auto light = make_shared<PointLight>(camera->position(), vec3(1, 1, 1), 100.0f);
        light->linkToCamera(camera);

        auto object = make_shared<ModelCube>(1.0f);
        object->setData(m_cubeData);
        object->setProgram(m_cubeProgram);
        object->setViewport(viewport);
        object->setProjection(projection);
        object->setCamera(camera);
        object->setLight(light);
        object->setRotation(vec3(10, 30, 40));
        object->setScale(1.0f);
        object->setPosition(vec3(-2, 8, 9));
        object->setColor(vec4(0, 1, 0, 1));
        object->setState(Object::APPEARING);
        object->setInteractive(true);

        auto object2 = make_shared<ModelCube>(1.0f);
        object2->setData(m_cubeData);
        object2->setProgram(m_cubeProgram);
        object2->setViewport(viewport);
        object2->setProjection(projection);
        object2->setCamera(camera);
        object2->setLight(light);
        object2->setRotation(vec3(45, -45, 45));
        object2->setScale(1.0f);
        object2->setPosition(vec3(3, 7, 7));
        object2->setColor(vec4(1, 0, 0, 1));
        object2->setState(Object::APPEARING);
        object2->setInteractive(true);

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
        m_modelObjects.push_back(object);
        m_modelingObjects.push_back(object);
        m_interactiveObjects.push_back(object);
        m_modelObjects.push_back(object2);
        m_modelingObjects.push_back(object2);
        m_interactiveObjects.push_back(object2);
        m_modelingObjects.push_back(grid);

        m_modelingViewport = viewport;
        m_modelingProjection = projection;
        m_modelingCamera = camera;
        m_modelingLight = light;
    }

    // Set up the add-button scene
    {
        auto viewport = make_shared<Viewport>(0, 0, m_screenWidth / 5, m_screenHeight / 5);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0, 2, 5), vec3(180, -30, -5));
        auto light = make_shared<PointLight>(vec3(0, 1, 10), vec3(1, 1, 1), 100.0f);
        auto object = make_shared<ActionCube>(1.0f);
        object->setData(m_cubeData);
        object->setProgram(m_cubeProgram);
        object->setViewport(viewport);
        object->setProjection(projection);
        object->setCamera(camera);
        object->setLight(light);
        object->setRotation(vec3(0, 0, 0));
        object->setScale(1.0f);
        object->setPosition(vec3(0, 0, 0));
        object->setColor(vec4(0, 0, 1, 1));
        object->setState(Object::NONE);
        object->setInteractive(true);

        m_viewports.push_back(viewport);
        m_projections.push_back(projection);
        m_cameras.push_back(camera);
        m_lights.push_back(light);
        m_hudObjects.push_back(object);
        m_interactiveObjects.push_back(object);

        m_actionCube = object;
    }

    // Set up the compass scene
    {
        auto viewport = make_shared<Viewport>(
            m_screenWidth - (m_screenWidth / 6), 0,
            m_screenWidth / 6, m_screenHeight / 6);
        auto projection = make_shared<mat4>(perspective(45.0f, 4.0f / 3.0f,  0.1f,  100.0f));
        auto camera = make_shared<Camera>(vec3(0, 0, 5), vec3(180, 0, 0));
        auto light = make_shared<PointLight>(camera->position(), vec3(1, 1, 1), 0.0f);
        auto compass = make_shared<Compass>(m_modelingCamera);
        compass->setData(make_shared<CompassData>());
        compass->setProgram(make_shared<CompassProgram>());
        compass->setViewport(viewport);
        compass->setProjection(projection);
        compass->setCamera(camera);
        compass->setLight(light);
        compass->setRotation(vec3(0, 0, 0));
        compass->setScale(2.0f);
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
}

void TheCubes::updateAndRender() {
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - m_lastTime);
    m_lastTime = currentTime;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto& object : m_modelingObjects) {
        object->update(deltaTime);
        object->render();
    }
    for (auto& object : m_hudObjects) {
        object->update(deltaTime);
        object->render();
    }
    glfwSwapBuffers();
}

void TheCubes::createNewObject() {
    auto object = make_shared<ModelCube>(1.0f);
    object->setData(m_cubeData);
    object->setProgram(m_cubeProgram);
    object->setViewport(m_modelingViewport);
    object->setProjection(m_modelingProjection);
    object->setCamera(m_modelingCamera);
    object->setLight(m_modelingLight);
    object->setRotation(vec3(10, 30, 40));
    object->setScale(1.0f);

    auto cameraBase = m_modelingCamera->base();
    auto pc = vec3(0, 0, 10);
    auto pw = (cameraBase * pc) + m_modelingCamera->position();
    object->setPosition(pw);
    object->setColor(vec4(0, 1, 0, 1));
    object->setState(Object::APPEARING);
    object->setInteractive(true);

    m_modelObjects.push_back(object);
    m_modelingObjects.push_back(object);
    m_interactiveObjects.push_back(object);
}

shared_ptr<Object> TheCubes::selectedObject(const vec2& mousePos) const {
    auto selection = shared_ptr<Object>();
    auto closestDistance = numeric_limits<float>::max();
    Viewport* viewport = nullptr;
    Camera* camera = nullptr;
    mat4* projectionMatrix = nullptr;
    auto ray = Geom::Ray(vec4(0.0f), vec4(0.0f));
    auto last = end(m_interactiveObjects);

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
            auto vpp = vec2(mousePos.x - vpx, m_screenHeight - mousePos.y - vpy);
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
            if (object == m_actionCube) {
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

void TheCubes::handleInput() {
    // Determine mouse and keyboard status.

    bool isShiftPressed = (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS);
    bool isControlPressed = (glfwGetKey(GLFW_KEY_LCTRL) == GLFW_PRESS);
    bool isAltPressed = (glfwGetKey(GLFW_KEY_LALT) == GLFW_PRESS);
    auto isMouseButtonPressStarted = false;
    auto isMouseClicked = false;
    bool isMouseMoved = false;
    bool isMousePosValid = false;
    auto mousePos = vec2(-1, -1);
    auto delta = vec2(0, 0);

    int mx, my;
    glfwGetMousePos(&mx, &my);
    mousePos = vec2(mx, my);
    delta = mousePos - m_lastMousePos;
    if (0 <= mx && mx < int(m_screenWidth)
        && 0 <= my && my < int(m_screenHeight)) {
        isMousePosValid = true;
        if (m_lastMousePos != mousePos) {
            isMouseMoved = true;
            m_lastMousePos = mousePos;
        }
    }

    auto mouseButtonState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    if (mouseButtonState == GLFW_PRESS) {
        if (!m_isMouseButtonPressed) {
            m_isMouseButtonPressed = true;
            isMouseButtonPressStarted = true;
        }
    }
    if (mouseButtonState == GLFW_RELEASE && m_isMouseButtonPressed) {
        // Mouse button was pressed and then released.
        m_isMouseButtonPressed = false;
        isMouseClicked = true;
    }

    // Act on input.

    switch (m_inputState) {
    case NONE:
        {
            if (!isShiftPressed && !isControlPressed && isMouseClicked && isMousePosValid) {
                // Clicked on object (press + release, not just press)
                auto object = selectedObject(m_lastMousePos);
                if (object && object != m_actionCube
                    && (object->state() == Object::HOVERED || object->state() == Object::NONE)) {
                    object->setState(Object::DISAPPEARING);
                }
            } else if (!isShiftPressed && !isControlPressed && !isAltPressed && isMouseMoved) {
                if (m_isMouseButtonPressed) {
                    auto object = selectedObject(m_lastMousePos);
                    if (object && object != m_actionCube) {
                        // Move object
                        m_movingObject = object;
                        m_inputState = MOVING_OBJECT;
                    } else {
                        // Move camera on (X, Y) plane
                        m_inputState = MOVING_CAMERA;
                    }
                } else if (isMousePosValid) {
                    // Hovering over objects
                    clearHoveredState();
                    auto object = selectedObject(m_lastMousePos);
                    if (object && object->state() == Object::NONE) {
                        object->setState(Object::HOVERED);
                    }
                }
            } else if (!isShiftPressed && !isControlPressed && !isAltPressed && isMouseButtonPressStarted) {
                auto object = selectedObject(m_lastMousePos);
                if (object == m_actionCube
                    && (object->state() == Object::NONE || object->state() == Object::HOVERED)) {
                    m_actionCube->setState(Object::PRESSED);
                    createNewObject();
                }
            } else if (isMouseMoved) {
                const auto f = 0.1f;
                if (isShiftPressed) {
                    // Pitch / Yaw camera
                    m_modelingCamera->updateAngles(vec3(delta.x * f, -delta.y * f, 0));
                } else if (isAltPressed) {
                    // Roll camera
                    m_modelingCamera->updateAngles(vec3(0, 0, -delta.y * f));
                } else if (isControlPressed) {
                    // Move camera along Z axis
                    m_modelingCamera->updatePosition(vec3(0, 0, -delta.y * f));
                }
            }
        }
        break;
    case MOVING_OBJECT:
        {
            if (m_isMouseButtonPressed) {
                const auto f = 0.01f;
                m_movingObject->updatePosition(vec3(delta.x * f, -delta.y * f, 0.0f));
            } else {
                m_movingObject = nullptr;
                m_inputState = NONE;
            }
        }
        break;
    case MOVING_CAMERA:
        {
            if (m_isMouseButtonPressed) {
                const auto f = 0.01f;
                m_modelingCamera->updatePosition(vec3(delta.x * f, delta.y * f, 0));
            } else {
                m_inputState = NONE;
            }
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
    vector<shared_ptr<Object>> clean;
    for (auto& object : m_modelObjects) {
        if (object->state() != Object::DEAD) {
            clean.push_back(object);
        }
    }
    m_modelObjects = clean;
}

void TheCubes::run() {
    bool exitting = false;
    m_lastTime = glfwGetTime();
    do {
        updateAndRender();
        handleInput();
        cleanupDeadModelObjects();
        if (!exitting &&
            (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS
             || (!glfwGetWindowParam(GLFW_OPENED)))) {
            killModelObjects();
            exitting = true;
        } 
    } while (!exitting || !m_modelObjects.empty());
}
