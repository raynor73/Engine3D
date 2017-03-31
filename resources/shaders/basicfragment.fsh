#version 330 core

in vec2 textureCoordinate0;

uniform sampler2D sampler;

out vec4 fragmentColor;

void main()
{
    fragmentColor = texture(sampler, textureCoordinate0.xy);
}
