#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 teWorldPosition[];
in vec4 teScreenPosition[];
in vec2 teUV[];
in vec4 vCol[];

out vec4 gWorldPosition;
out vec4 gScreenPosition;
out vec2 gUV;
out vec4 gCol;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

void main()
{
	mat4 pvmMatrix = Projection * View * Model;

	for( int i=0; i<3; ++i )
	{
		gl_Position		= pvmMatrix * ( teWorldPosition[i] );
		gWorldPosition	= teWorldPosition[i];
		gUV				= teUV[i];
		gScreenPosition	= teScreenPosition[i];
		EmitVertex();
	}

	EndPrimitive();
}