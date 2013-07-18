#include "object.h"

#include <glm/glm.hpp> // vec*, mat*
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

using namespace std;
using namespace glm;

Object::Object()
    : m_id(-1),
      m_viewport(nullptr),
      m_projectionMatrix(nullptr),
      m_camera(nullptr),
      m_light(nullptr),
      m_isModelMatrixValid(false),
      m_isUnscaledModelMatrixValid(false),
      m_isInteractive(false),
      m_angle(vec3(0.0f)),
      m_scale(1.0f),
      m_position(vec3(0.0f)),
      m_color(vec4(1.0f, 1.0f, 1.0f, 0.0f)),
      m_state(APPEARING) {
}

Object::~Object() {
}

void Object::setId(int id) {
    m_id = id;
}

void Object::setViewport(std::shared_ptr<const Viewport> viewport) {
    m_viewport = viewport;
}

void Object::setProjection(std::shared_ptr<const glm::mat4> projectionMatrix) {
    m_projectionMatrix = projectionMatrix;
}

void Object::setCamera(std::shared_ptr<const Camera> camera) {
    m_camera = camera;
}

void Object::setLight(std::shared_ptr<const PointLight> light) {
    m_light = light;
}

void Object::setRotation(glm::vec3 angle) {
    m_isModelMatrixValid = false;
    m_isUnscaledModelMatrixValid = false;
    m_angle = angle;
}

void Object::setScale(GLfloat scale) {
    m_isModelMatrixValid = false;
    m_isUnscaledModelMatrixValid = false;
    m_scale = scale;
}

void Object::setPosition(glm::vec3 position) {
    m_isModelMatrixValid = false;
    m_isUnscaledModelMatrixValid = false;
    m_position = position;
}

void Object::setColor(glm::vec4 color) {
    m_color = color;
}

void Object::setState(unsigned int state) {
    m_state = state;
}

unsigned int Object::state() const {
    return m_state;
}

void Object::setInteractive(bool isInteractive) {
    m_isInteractive = isInteractive;
}

bool Object::isInteractive() const {
    return m_isInteractive;
}

void Object::updatePosition(const vec3& delta) {
    const auto& p = vec4(m_position.x, m_position.y, m_position.z, 1);
    auto pc = m_camera->viewMatrix() * p;
    pc.x = pc.x + delta.x;
    pc.y = pc.y + delta.y;
    pc.z = pc.z + delta.z;
    const auto& I = inverse(m_camera->viewMatrix());
    const auto& pw = I * pc;
    m_position = vec3(pw.x, pw.y, pw.z);
    m_isModelMatrixValid = false;
    m_isUnscaledModelMatrixValid = false;
}

int Object::id() const {
    return m_id;
}

std::shared_ptr<const Viewport> Object::viewport() const {
    return m_viewport;
}

shared_ptr<const mat4> Object::projectionMatrix() const {
    return m_projectionMatrix;
}

shared_ptr<const Camera> Object::camera() const {
    return m_camera;
}

shared_ptr<const PointLight> Object::light() const {
    return m_light;
}

const glm::vec3& Object::angle() const {
    return m_angle;
}

GLfloat Object::scale() const {
    return m_scale;
}

const glm::vec3& Object::position() const {
    return m_position;
}

const glm::vec4& Object::color() const {
    return m_color;
}

Geom::Sphere Object::boundingSphere() const {
    return Geom::Sphere(vec4(m_position, 1),
                        m_scale * sqrt(3.0f));
}

mat4 Object::modelMatrix() {
    if (!m_isModelMatrixValid) {
        m_modelMatrix = calculateModelMatrix(true);
        m_isModelMatrixValid = true;
    }
    return m_modelMatrix;
}

const mat4& Object::unscaledModelMatrix() {
    if (!m_isUnscaledModelMatrixValid) {
        m_unscaledModelMatrix = calculateModelMatrix(false);
        m_isUnscaledModelMatrixValid = true;
    }
    return m_unscaledModelMatrix;
}

mat4 Object::calculateModelMatrix(bool withScaling) const {
    const auto& translated = translate(mat4(1.0f), m_position);
    const auto& scaled =
        withScaling
        ? glm::scale(translated, vec3(m_scale))
        : translated;
    const auto& rotZ = rotate(scaled, m_angle.z, vec3(0,0,1));
    const auto& rotY = rotate(rotZ, m_angle.y, vec3(0,1,0));
    const auto& rotX = rotate(rotY, m_angle.x, vec3(1,0,0));
    return rotX;
}

void Object::update(double deltaTime) {
}

void Object::render() {
}
