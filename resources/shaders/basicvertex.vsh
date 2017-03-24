#version 330 core

layout(location = 0) in vec3 position;

out vec4 color;

void main() {
    color = vec4(clamp(position, 0, 1), 1);
    gl_Position = vec4(position, 1);
}
