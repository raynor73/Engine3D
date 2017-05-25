#version 330 core

in vec2 textureCoordinate0;

uniform vec3 R_ambient;
uniform sampler2D R_diffuse;

out vec4 fragmentColor;

void main()
{
	fragmentColor = texture(R_diffuse, textureCoordinate0.xy) * vec4(R_ambient, 1);
}
