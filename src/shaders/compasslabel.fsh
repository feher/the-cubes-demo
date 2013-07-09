#version 120

uniform vec4 u_color; // For debugging purposes.
uniform sampler2D u_textureSampler;

varying vec2 v_vertexUv;

void main() {
  vec4 color = texture2D(u_textureSampler, v_vertexUv);
  gl_FragColor.rgb = color.rgb;
  gl_FragColor.a = color.a;
}
