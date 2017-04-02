#version 330 core

in vec2 textureCoordinate0;

uniform vec3 color;
uniform sampler2D sampler;

out vec4 fragmentColor;

void main()
{
	vec4 textureColor = texture(sampler, textureCoordinate0.xy);

	if (textureColor == vec4(0, 0, 0, 1))
		fragmentColor = vec4(color, 1);
	else
		fragmentColor = textureColor * vec4(color, 1);
}
