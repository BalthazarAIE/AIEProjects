#version 330

in vec4 Position;
in vec2 UV;

out vec4 vPosition;
out vec2 vUV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	//vScreenPosition	= Projection * View * Model * Position;
	gl_Position	= Position;
	vUV			= UV;
	//vSize	= Size;
}
