#version 400

in vec4 Position;
in vec2 UV;

out vec4 vScreenPosition;
out vec2 vUV;

void main()
{
	gl_Position		= Position;
	vScreenPosition = Position;
	vUV				= UV;
}
