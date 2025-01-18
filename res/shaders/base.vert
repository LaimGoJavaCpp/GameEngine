#version 330

in vec3 position;

uniform float time;

out float out_time;

void main()
{
	out_time = time;
	gl_Position = vec4(position,1);
}