#version 400

in vec4 Position;
in vec2 UV;

out vec2 vUV;

void main()
{
	gl_Position	= Position;
	vUV			= UV;
}
