#version 330 core

out vec4 color;
in float out_time;
void main()
{
	float r = sin(out_time) + 1.2;

	color = vec4(0,0,r/2,1);
}