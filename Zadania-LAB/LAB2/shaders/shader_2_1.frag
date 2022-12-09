#version 430 core

uniform float Otime;
 out vec4 out_color;
 in vec4 VC;
 in vec4 pos_local;
 in vec4 pos_global;
void main()
{
	
	 //out_color = (VC/Otime);
	out_color = pos_global;
}