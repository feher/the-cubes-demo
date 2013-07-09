#version 120

// Variable name prefixes:
// a: attribute
// u: uniform
// v: varying
// m: model space
// c: camera space
// w: world space

uniform vec4 u_color;
uniform mat4 u_mvp;

attribute vec3 am_vertexPosition;

void main() {
  gl_Position = u_mvp * vec4(am_vertexPosition, 1);
}

