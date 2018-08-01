#version 330 core

out vec4 FragColor;
uniform vec4 uniColor;
in vec4 Color;
in vec2 TexCoord0;
uniform sampler2D gSampler;

void main()
{
	
	FragColor = texture2D(gSampler, TexCoord0.xy);
}