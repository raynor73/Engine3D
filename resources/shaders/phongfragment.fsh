#version 330 core

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

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

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform vec3 baseColor;
uniform vec3 eyePosition;
uniform vec3 ambientLight;
uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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

vec4 calculateSpotLight(SpotLight spotLight, vec3 normal)
{
	vec3 direction = normalize(worldPosition0 - spotLight.pointLight.position);
	float spotFactor = dot(direction, spotLight.direction);

	vec4 color = vec4(0, 0, 0, 0);

	if (spotFactor > spotLight.cutoff) {
		color = calculatePointLight(spotLight.pointLight, normal) *
		        (1 - (1 - spotFactor) / (1 - spotLight.cutoff));
	}

	return color;
}

void main()
{
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);
	vec4 textureColor = texture(sampler, textureCoordinate0.xy);

	if (textureColor != vec4(0, 0, 0, 1))
		color *= textureColor;

	vec3 normal = normalize(normal0);
	totalLight += calculateDirectionalLight(directionalLight, normal);

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		if (pointLights[i].base.intensity > 0)
			totalLight += calculatePointLight(pointLights[i], normal);

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
		if (spotLights[i].pointLight.base.intensity > 0)
			totalLight += calculateSpotLight(spotLights[i], normal);

	fragmentColor = color * totalLight;
}
