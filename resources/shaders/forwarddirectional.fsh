#version 330 core
#include "lighting.glh"

in vec2 textureCoordinate0;
in vec3 normal0;
in vec3 worldPosition0;

out vec4 fragmentColor;

uniform sampler2D diffuse;
uniform DirectionalLight R_directionalLight;

void main()
{
	fragmentColor =
			texture(diffuse, textureCoordinate0.xy) *
			calculateDirectionalLight(R_directionalLight, normalize(normal0), worldPosition0);
}
