#version 400

layout( vertices = 3 ) out;

in vec2 vUV[];
in vec4 vWorldPosition[];

out vec2 tcUV[];
out vec4 tcWorldPosition[];

uniform float Time;
uniform vec4 CameraPos;
uniform sampler2D diffuseTexture;
uniform sampler2D secondaryTexture;
uniform vec4 Colour;

void main()
{
	gl_out[ gl_InvocationID ].gl_Position = gl_in[ gl_InvocationID ].gl_Position;
	tcUV[gl_InvocationID] = vUV[gl_InvocationID];
	tcWorldPosition[gl_InvocationID] = vWorldPosition[gl_InvocationID];

	vec4 vDist			= tcWorldPosition[gl_InvocationID] - CameraPos;
	float fDist			= sqrt( vDist.x*vDist.x + vDist.y*vDist.y + vDist.z*vDist.z );
	float subDivisions	= 6 - (fDist * 0.02);
	subDivisions		= floor(subDivisions);
	subDivisions		= clamp( subDivisions, 1, 10 );

	gl_TessLevelOuter[ 0 ] = 1;
	gl_TessLevelOuter[ 1 ] = 1;
	gl_TessLevelOuter[ 2 ] = 1;
	gl_TessLevelInner[ 0 ] = 1;
}
