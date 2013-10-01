#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 teWorldPosition[];
in vec4 teScreenPosition[];
in vec2 teUV[];

out vec4 gWorldPosition;
out vec4 gScreenPosition;
out vec2 gUV;
out vec4 gCol;
out vec4 gNormal;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

void main()
{
	mat4 pvmMatrix = Projection * View * Model;

	vec4 norm = vec4( cross( teWorldPosition[0].xyz - teWorldPosition[1].xyz,
						teWorldPosition[2].xyz - teWorldPosition[0].xyz ), 0 );
	gNormal = normalize( norm );

	for( int i=0; i<3; ++i )
	{
		gl_Position		= pvmMatrix * ( teWorldPosition[i] );
		gWorldPosition	= teWorldPosition[i];
		gScreenPosition = teScreenPosition[i];
		gUV				= teUV[i];
		EmitVertex();
	}

	EndPrimitive();
}