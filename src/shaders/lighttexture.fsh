uniform vec3 uw_lightPosition;
uniform vec3 u_lightColor;
uniform float u_lightPower;
uniform float u_highlightFactor;
uniform sampler2D u_textureSampler;
uniform vec3 u_materialAmbientFactor;
uniform vec3 u_materialSpecularFactor;

varying vec3 vw_vertexPosition;
varying vec3 vc_vertexNormal;
varying vec2 v_vertexUv;
varying vec3 vc_eyeDirection;
varying vec3 vc_lightDirection;

const float ZERO = 0.0;

#ifdef USE_SHADOW_MAP
uniform sampler2DShadow u_shadowTextureSampler;
uniform vec3 uw_directionalLightDirection;
varying vec3 vw_vertexNormal;
varying vec4 v_vertexShadowMapUv;
#endif

vec4 light(vec4 color) {
  vec3 materialDiffuseFactor = clamp(color * u_highlightFactor, 0, 255).rgb;

  float lightDistance = length(uw_lightPosition - vw_vertexPosition);

  vec3 c_vertexNormal = normalize(vc_vertexNormal);
  vec3 c_lightDirection = normalize(vc_lightDirection);
  float cosDiffuse = clamp(dot(c_vertexNormal, c_lightDirection), 0, 1);
	
  vec3 c_eyeDirection = normalize(vc_eyeDirection);
  vec3 c_reflection = reflect(-c_lightDirection, c_vertexNormal);
  float cosSpecular = clamp(dot(c_eyeDirection, c_reflection), 0, 1);

  float shadowFactor = 1.0;
  
#ifdef USE_SHADOW_MAP
  vec3 w_vertexNormal = normalize(vw_vertexNormal);
  float x = dot(w_vertexNormal, uw_directionalLightDirection);
  float bias = (1.0 - (x + 1.0) / 2.0) * 0.005;
  vec3 uv = vec3(v_vertexShadowMapUv.xy / v_vertexShadowMapUv.w,
                 (v_vertexShadowMapUv.z - bias) / v_vertexShadowMapUv.w);
  if (v_vertexShadowMapUv.w > 0.0) {
    const float d = 1.0 / 1024.0;
    float f = 0.0;
    float s, t, z;
    int i, j, k;
    for (i = 0, t = uv.t - d; i < 3; ++i, t += d) {
      for (j = 0, s = uv.s - d; j < 3; ++j, s += d) {
        for (k = 0, z = uv.z - d; k < 3; ++k, z += d) {
          f += shadow2D(u_shadowTextureSampler, vec3(s, t, z)).r;
        }
      }
    }
    f /= 27.0;
    shadowFactor = f;
  }
#endif

  vec4 outColor;
  outColor.rgb = 
      u_materialAmbientFactor * materialDiffuseFactor
      + materialDiffuseFactor * u_lightColor * u_lightPower * shadowFactor
        * cosDiffuse / (lightDistance * lightDistance) +
      + u_materialSpecularFactor * u_lightColor * u_lightPower * shadowFactor
        * pow(cosSpecular, 5) / (lightDistance * lightDistance);

  outColor.a = color.a;
  return outColor;
}

void main() {
  vec4 color = texture2D(u_textureSampler, v_vertexUv);
  if (u_lightPower >= ZERO) {
    gl_FragColor = light(color);
  } else {
    gl_FragColor = color; // For debugging.
  }
}
