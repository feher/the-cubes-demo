// Variable name prefixes:
// a: attribute
// u: uniform
// v: varying
// t: tangent space
// m: model space
// c: camera space
// w: world space

uniform mat4 u_mvp;   // Model-View-Projection matrix.
uniform mat4 u_v;     // View matrix.
uniform mat4 u_m;     // Model matrix.
uniform mat4 u_mns;   // Model matrix without scaling.
uniform vec3 uw_lightPosition;
uniform vec3 u_lightColor;
uniform float u_lightPower;
uniform float u_highlightFactor;

attribute vec3 am_vertexPosition;
attribute vec3 am_vertexNormal;
attribute vec3 am_vertexTangent;
attribute vec3 am_vertexBitangent;
attribute vec2 a_vertexUv;

varying vec3 vw_vertexPosition;
varying vec3 vt_eyeDirection;
varying vec3 vt_lightDirection;
varying vec2 v_vertexUv;

const float ZERO = 0.0;

#ifdef USE_SHADOW_MAP
uniform mat4 u_shadowMvp;
uniform vec3 uw_directionalLightDirection;
varying vec3 vw_vertexNormal;
varying vec4 v_vertexShadowMapUv;
#endif

void light() {
  vw_vertexPosition = (u_m * vec4(am_vertexPosition, 1)).xyz;

  vec3 c_vertexPosition = (u_v * u_m * vec4(am_vertexPosition, 1)).xyz;
  vec3 c_eyeDirection = vec3(0,0,0) - c_vertexPosition;

  vec3 c_lightPosition = (u_v * vec4(uw_lightPosition, 1)).xyz;
  vec3 c_lightDirection = c_lightPosition + c_eyeDirection;

  // ntMV : ModelView matrix without translation.
  mat3 ntMV = mat3(u_v) * mat3(u_mns);
  // T : takes from tangent space to camera space.
  vec3 c_vertexTangent = ntMV * am_vertexTangent;
  vec3 c_vertexBitangent = ntMV * am_vertexBitangent;
  vec3 c_vertexNormal = ntMV * am_vertexNormal;
  // invT : takes from camera space to tangent space.
  mat3 invT = transpose(mat3(c_vertexTangent, c_vertexBitangent, c_vertexNormal));
  vt_eyeDirection = invT * c_eyeDirection;
  vt_lightDirection = invT * c_lightDirection;
}

void main() {
  if (u_lightPower >= ZERO) {
    light();
  }

#ifdef USE_SHADOW_MAP
  v_vertexShadowMapUv = u_shadowMvp * vec4(am_vertexPosition, 1);
  vw_vertexNormal = (u_mns * vec4(am_vertexNormal, 0)).xyz;
#endif
  
  v_vertexUv = a_vertexUv;
  gl_Position = u_mvp * vec4(am_vertexPosition, 1);
}

