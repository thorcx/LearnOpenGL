#version 330 core

out vec4 FragColor;
uniform vec4 uniColor;
in vec4 Color;

void main()
{
	FragColor = Color;
}