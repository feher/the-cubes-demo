// Variable name prefixes:
// a: attribute
// u: uniform
// v: varying
// m: model space
// c: camera space
// w: world space

uniform mat4 u_mvp; // Model-View-Projection matrix.

attribute vec3 am_vertexPosition;
attribute vec2 a_vertexUv;

varying vec2 v_vertexUv;

void main() {
  v_vertexUv = a_vertexUv;
  gl_Position = u_mvp * vec4(am_vertexPosition, 1);
}

