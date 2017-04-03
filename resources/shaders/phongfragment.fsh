#version 330 core

in vec2 textureCoordinate0;

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

out vec4 fragmentColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(-direction, normal);
	vec4 diffuseColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0) {
		diffuseColor = vec4(base.color, 1) * base.intensity * diffuseFactor;
	}

	return diffuseColor;
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calculateLight(directionalLight.base, directionalLight.direction, normal);
}

void main()
{
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);
	vec4 textureColor = texture(sampler, textureCoordinate0.xy);

	if (textureColor != vec4(0, 0, 0, 1))
		color *= textureColor;

	fragmentColor = color * totalLight;
}
