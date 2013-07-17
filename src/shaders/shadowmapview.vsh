attribute vec3 am_vertexPosition;

varying vec2 v_vertexUv;

void main(){
  gl_Position = vec4(am_vertexPosition, 1.0);
  v_vertexUv = (am_vertexPosition.xy + vec2(1, 1)) / 2.0;
}

