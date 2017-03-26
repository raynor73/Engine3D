#version 330 core

layout(location = 0) in vec3 position;

out vec4 color;

uniform mat4 transform;

void main() {
    color = transform * vec4(clamp(position, 0, 1), 1);
    gl_Position = transform * vec4(position, 1);
}
