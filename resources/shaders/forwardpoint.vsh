#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinate;
layout(location = 2) in vec3 normal;

out vec2 textureCoordinate0;
out vec3 normal0;
out vec3 worldPosition0;

uniform mat4 T_model;
uniform mat4 T_modelViewProjection;

void main() {
	gl_Position = T_modelViewProjection * vec4(position, 1);
	textureCoordinate0 = textureCoordinate;
	normal0 = (T_model * vec4(normal, 0)).xyz;
	worldPosition0 = (T_model * vec4(position, 1)).xyz;
}
