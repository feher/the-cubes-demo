#version 120

uniform vec4 u_color;

void main() {
  gl_FragColor.rgb = u_color.rgb;
}