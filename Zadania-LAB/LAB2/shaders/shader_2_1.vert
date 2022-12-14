#version 430 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;

uniform mat4 transformation;


out vec4 VC;
out vec4 pos_local;
out vec4 pos_global;

void main()
{
	VC = vertexColor;
	pos_local = vertexPosition;
	pos_global = transformation * vertexPosition;
	gl_Position = transformation * vertexPosition;
	
}
