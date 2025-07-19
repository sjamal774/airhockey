#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform float time;

vec3 pastelRainbow(float t) {
    float r = 0.5 + 0.5 * sin(t + 0.0);
    float g = 0.5 + 0.5 * sin(t + 2.0);
    float b = 0.5 + 0.5 * sin(t + 4.0);
    return vec3(r, g, b) * 0.8 + 0.2; // pastel shift
}

void main() {
    vec4 texColor = texture(image, TexCoords);
    vec3 tint = pastelRainbow(time);
    FragColor = vec4(texColor.rgb * tint, texColor.a);
}