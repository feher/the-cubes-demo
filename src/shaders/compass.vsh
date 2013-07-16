// Variable name prefixes:
// a: attribute
// u: uniform
// v: varying
// m: model space
// c: camera space
// w: world space

uniform mat4 u_mvp;

attribute vec3 am_vertexPosition;
attribute vec3 a_vertexColor;

varying vec3 v_vertexColor;

void main() {
  v_vertexColor = a_vertexColor;
  gl_Position = u_mvp * vec4(am_vertexPosition, 1);
}

