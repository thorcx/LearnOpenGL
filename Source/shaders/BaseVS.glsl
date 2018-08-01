#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

uniform float gScale;
uniform mat4 gWVP;

out vec4 Color;
out vec2 TexCoord0;

void main()
{
	gl_Position = gWVP * vec4(Position, 1.0);
	Color = vec4(clamp(Position, 0.0, 1.0),1.0);
	TexCoord0 = TexCoord;
}