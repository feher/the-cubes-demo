#version 120

uniform vec4 u_color; // For debugging.

varying vec3 v_vertexColor;

void main() {
  gl_FragColor.rgb = v_vertexColor.rgb;
}
