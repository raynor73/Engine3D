#version 330 core

in vec2 textureCoordinate0;

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

out vec4 fragmentColor;

void main()
{
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);
	vec4 textureColor = texture(sampler, textureCoordinate0.xy);

	if (textureColor != vec4(0, 0, 0, 1))
		color *= textureColor;

	fragmentColor = color * totalLight;
}
