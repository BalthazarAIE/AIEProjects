#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 teWorldPosition[];
in vec4 vScreenPosition[];
in vec2 teUV[];
in vec4 vCol[];

out vec4 gWorldPosition;
out vec4 gPosition;
out vec2 gUV;
out vec4 gCol;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

void main()
{
	mat4 pvmMatrix = Projection * View * Model;

	/////////////
	//PLAIN 
	//////////////

	for( int i=0; i<3; ++i )
	{
		gl_Position		= pvmMatrix * ( teWorldPosition[i] );
		gWorldPosition	= teWorldPosition[i];
		gUV				= teUV[i];
		EmitVertex();
	}

	/////////////
	//Explode
	/////////////
	//vec4 dir = vec4( cross( teWorldPosition[0].xyz - teWorldPosition[1].xyz,
	//						teWorldPosition[2].xyz - teWorldPosition[1].xyz	), 0 );

	//dir = normalize( dir );
	//mat4 pvmMatrix = Projection * View * Model;

	//for( int i=0; i<3; ++i )
	//{
	//	gl_Position = pvmMatrix * ( teWorldPosition[i] - dir  * cos(Time) );
	//	gUV			= teUV[i];
	//	gCol		= vCol[i];
	//	EmitVertex();
	//}

	EndPrimitive();
}