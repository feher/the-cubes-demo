uniform sampler2D u_textureSampler;

varying vec2 v_vertexUv;

void main(){
  gl_FragColor = texture2D(u_textureSampler, v_vertexUv);
}
