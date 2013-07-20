uniform vec3 uw_lightPosition;
uniform vec3 u_lightColor;
uniform float u_lightPower;
uniform float u_highlightFactor;
uniform sampler2D u_textureSampler;
uniform sampler2D u_normalSampler;
uniform vec3 u_materialAmbientFactor;
uniform vec3 u_materialSpecularFactor;

varying vec3 vw_vertexPosition;
varying vec2 v_vertexUv;
varying vec3 vt_eyeDirection;
varying vec3 vt_lightDirection;

const float ZERO = 0.0;

#ifdef USE_SHADOW_MAP
uniform sampler2DShadow u_shadowTextureSampler;
uniform vec3 uw_directionalLightDirection;
varying vec3 vw_vertexNormal;
varying vec4 v_vertexShadowMapUv;
#endif

vec4 light(vec4 color) {
    vec3 materialDiffuseFactor = clamp(color * u_highlightFactor, 0.0, 1.0).rgb;

    float lightDistance = length(uw_lightPosition - vw_vertexPosition);

    vec3 t_vertexNormal = normalize(
                          texture2D(u_normalSampler, v_vertexUv).rgb
                          // The map value is in [0, 1] but we need it
                          // in [-1, 1] to represent a vector.
                          * 2.0 - vec3(1.0));
  
    vec3 t_lightDirection = normalize(vt_lightDirection);
    float cosDiffuse = clamp(dot(t_vertexNormal, t_lightDirection), 0, 1);
	
    vec3 t_eyeDirection = normalize(vt_eyeDirection);
    vec3 t_reflection = reflect(-t_lightDirection, t_vertexNormal);
    float cosSpecular = clamp(dot(t_eyeDirection, t_reflection), 0, 1);

    float shadowFactor = 1.0;
  
#ifdef USE_SHADOW_MAP
    // We want 0 bias when the light is full frontal.
    // x is in [-1, 1]. It is 1 when the light is full frontal.
    // We map x into [0, 1] and flip it around to get our bias.
    vec3 w_vertexNormal = normalize(vw_vertexNormal);
    float x = dot(w_vertexNormal, uw_directionalLightDirection);
    const float fullBias = 0.005;
    float bias = (1.0 - (x + 1.0) / 2.0) * fullBias;

    // Take the average of the visibility information around our pixel.
    // This manages to get rid of most of the acne and other artefacts.
    // NOTE: the choice of the AREA * AREA * AREA value is arbitrary.
    vec3 uv = vec3(v_vertexShadowMapUv.xy / v_vertexShadowMapUv.w,
                   (v_vertexShadowMapUv.z - bias) / v_vertexShadowMapUv.w);
    if (v_vertexShadowMapUv.w > 0.0) {
        int AREA = 0;
        if (-0.3 < x && x < 0.3) {
            AREA = 3;
        } else {
            AREA = 2;
        }
        const float SHADOW_MAP_SIZE = 1024.0;
        const float d = 1.0 / SHADOW_MAP_SIZE;
        float f = 0.0;
        float s, t, z;
        int i, j, k;
        for (i = 0, t = uv.t - d; i < AREA; ++i, t += d) {
          for (j = 0, s = uv.s - d; j < AREA; ++j, s += d) {
            for (k = 0, z = uv.z - d; k < AREA; ++k, z += d) {
              f += shadow2D(u_shadowTextureSampler, vec3(s, t, z)).r;
            }
          }
        }
        f /= (AREA * AREA * AREA);
        // Fix up the brightness we lost due to the averaging.
        const float FIX = 1.6;
        shadowFactor = clamp(f * FIX, 0.0, 1.0);
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
