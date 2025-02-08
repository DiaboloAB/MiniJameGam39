#version 330

uniform float time;
uniform vec2 resolution;

out vec4 fragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 center = vec2(0.5, 0.5);
    float distance = length(uv - center);

    // Heartbeat effect
    float beat = sin(time * 10.0) * 0.5 + 0.5;
    float beat2 = sin(time * 20.0) * 0.5 + 0.5;

    // Adjust distance based on beat
    float adjustedDistance = distance * (1.0 + beat * 0.05 + beat2 * 0.10);

    // Intensity based on adjusted distance
    float intensity = (1.0 - 0.8) * beat;

    // White overlay effect with transparency
    vec3 whiteColor = vec3(1.0, 1.0, 1.0);
    float alpha = intensity * smoothstep(0.4, 0.5, adjustedDistance);

    fragColor = vec4(whiteColor, alpha);
}