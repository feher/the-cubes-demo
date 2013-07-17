// Variable name prefixes:
// a: attribute
// u: uniform
// v: varying
// m: model space
// c: camera space
// w: world space

attribute vec3 am_vertexPosition;

uniform mat4 u_mvp;

void main(){
  gl_Position = u_mvp * vec4(am_vertexPosition, 1);
}

