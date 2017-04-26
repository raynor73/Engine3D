#version 330 core

in vec2 textureCoordinate0;
in vec3 normal0;
in vec3 worldPosition0;

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

uniform vec3 eyePosition;
uniform sampler2D diffuse;

uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0, 0, 0, 0);
	vec4 specularColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0) {
		diffuseColor = vec4(base.color, 1) * base.intensity * diffuseFactor;

		vec3 directionToEye = normalize(eyePosition - worldPosition0);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = dot(directionToEye, reflectDirection);
		specularFactor = pow(specularFactor, specularPower);

		if (specularFactor > 0) {
			specularColor = vec4(base.color, 1) * specularIntensity * specularFactor;
		}
	}

	return diffuseColor + specularColor;
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calculateLight(directionalLight.base, -directionalLight.direction, normal);
}

void main()
{
	fragmentColor =
			texture(diffuse, textureCoordinate0.xy) *
			calculateDirectionalLight(directionalLight, normalize(normal0));
}
