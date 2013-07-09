#version 120

varying vec3 vw_vertexPosition;
varying vec3 vc_vertexNormal;
varying vec2 v_vertexUv;
varying vec3 vc_eyeDirection;
varying vec3 vc_lightDirection;

uniform vec4 u_color;
uniform vec3 uw_lightPosition;
uniform vec3 u_lightColor;
uniform float u_lightPower;
uniform float u_highlightFactor;
uniform sampler2D u_textureSampler;

vec4 light(vec4 color) {
  vec3 materialDiffuseColor = clamp(color * u_highlightFactor, 0, 255).rgb;
  vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
  vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

  float lightDistance = length(uw_lightPosition - vw_vertexPosition);

  vec3 c_vertexNormal = normalize(vc_vertexNormal);
  vec3 c_lightDirection = normalize(vc_lightDirection);
  float cosDiffuse = clamp(dot(c_vertexNormal, c_lightDirection), 0, 1);
	
  vec3 c_eyeDirection = normalize(vc_eyeDirection);
  vec3 c_reflection = reflect(-c_lightDirection, c_vertexNormal);
  float cosSpecular = clamp(dot(c_eyeDirection, c_reflection), 0, 1);

  vec4 outColor;
  outColor.rgb = 
      materialAmbientColor
      + materialDiffuseColor * u_lightColor * u_lightPower
        * cosDiffuse / (lightDistance * lightDistance) +
      + materialSpecularColor * u_lightColor * u_lightPower
        * pow(cosSpecular, 5) / (lightDistance * lightDistance);

  outColor.a = color.a;
  return outColor;
}

vec4 noLight(vec4 color) {
  return color;
}

void main() {
  vec4 color = texture2D(u_textureSampler, v_vertexUv);

  float ZERO = float(1.0);
  if (u_lightPower < ZERO) {
    gl_FragColor = noLight(color);
  } else {
    gl_FragColor = light(color);
  }
}
