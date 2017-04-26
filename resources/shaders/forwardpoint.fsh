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

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	BaseLight base;
	Attenuation attenuation;
	vec3 position;
	float range;
};

uniform vec3 eyePosition;
uniform sampler2D diffuse;

uniform float specularIntensity;
uniform float specularPower;

uniform PointLight pointLight;

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

vec4 calculatePointLight(PointLight pointLight, vec3 normal)
{
	vec3 direction = worldPosition0 - pointLight.position;
	float distance = length(direction);

	if (distance > pointLight.range)
		return vec4(0, 0, 0, 0);

	direction = normalize(direction);

	vec4 color = calculateLight(pointLight.base, direction, normal);

	float attenuation =
	        pointLight.attenuation.constant +
	        pointLight.attenuation.linear * distance +
	        pointLight.attenuation.exponent * distance * distance +
	        0.0001;

	return color / attenuation;
}

void main()
{
	fragmentColor =
	        texture(diffuse, textureCoordinate0.xy) *
	        calculatePointLight(pointLight, normalize(normal0));
}
