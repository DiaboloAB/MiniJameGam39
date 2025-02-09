#version 330

uniform float time;
uniform vec2 resolution;
uniform float health;

out vec4 fragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 center = vec2(0.5, 0.5);
    float distance = length(uv - center);

    // Heartbeat effect
    float beat = sin(time * 10.0) * 0.5 + 0.5;

    // Intensity based on health
    float intensity = (1.0 - health) * beat;

    // Red overlay effect with transparency
    vec3 redColor = vec3(1.0, 0.0, 0.0);
    float alpha = intensity * smoothstep(0.4, 0.5, distance);

    fragColor = vec4(redColor, alpha);
}