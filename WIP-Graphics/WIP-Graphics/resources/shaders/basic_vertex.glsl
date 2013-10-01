#version 400

in vec4 Position;
in vec2 UV;

out vec4 vWorldPosition;
out vec4 vScreenPosition;
out vec2 vUV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	vUV = UV;

	vWorldPosition	= Position;
	vScreenPosition	= Projection * View * Model * vWorldPosition;
	
	gl_Position = vScreenPosition;
}
