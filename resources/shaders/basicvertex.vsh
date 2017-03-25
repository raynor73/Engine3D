#version 330 core

layout(location = 0) in vec3 position;

out vec4 color;

uniform float uniformFloat;

void main() {
    color = vec4(clamp(position, 0, uniformFloat), 1);
    gl_Position = vec4(position, 1);
}
