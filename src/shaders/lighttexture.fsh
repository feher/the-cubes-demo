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

vec4 light(vec4 color) {
  vec3 materialDiffuseFactor = clamp(color * u_highlightFactor, 0, 255).rgb;

  float lightDistance = length(uw_lightPosition - vw_vertexPosition);

  vec3 c_vertexNormal = normalize(vc_vertexNormal);
  vec3 c_lightDirection = normalize(vc_lightDirection);
  float cosDiffuse = clamp(dot(c_vertexNormal, c_lightDirection), 0, 1);
	
  vec3 c_eyeDirection = normalize(vc_eyeDirection);
  vec3 c_reflection = reflect(-c_lightDirection, c_vertexNormal);
  float cosSpecular = clamp(dot(c_eyeDirection, c_reflection), 0, 1);

  vec4 outColor;
  outColor.rgb = 
      u_materialAmbientFactor * materialDiffuseFactor
      + materialDiffuseFactor * u_lightColor * u_lightPower
        * cosDiffuse / (lightDistance * lightDistance) +
      + u_materialSpecularFactor * u_lightColor * u_lightPower
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
