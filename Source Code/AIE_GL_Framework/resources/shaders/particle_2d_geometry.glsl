#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 vWorldPosition[];
in vec4 vScreenPosition[];
in vec2 vSize[];
in float vAlpha[];

out vec2 gUV;
out float gAlpha;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

uniform mat4 CameraMat;

void main()
{
	vec2 halfSize	= vSize[0] * 0.5f;
	mat4 pvmMatrix	= Projection * View * Model;

	vec3 cameraPos;
	cameraPos.x = CameraMat[3][0];
	cameraPos.y = CameraMat[3][1];
	cameraPos.z = CameraMat[3][2];

	vec3 cameraUp;
	cameraUp.x	= CameraMat[1][0];
	cameraUp.y	= CameraMat[1][1];
	cameraUp.z	= CameraMat[1][2];
	cameraUp	= normalize( cameraUp );

	vec3 look	= normalize( cameraPos.xyz - vWorldPosition[0].xyz );
	vec3 right	= cross( cameraUp.xyz,	look.xyz	);
	vec3 up		= cross( look.xyz,		right.xyz	);

	vec3 X		= halfSize.x*right;
	vec3 Y		= halfSize.y*up;

	gl_Position = pvmMatrix * ( vWorldPosition[0] - vec4(X, 0) + vec4(Y, 0) );
	gUV		= vec2( 1, 1 );
	gAlpha	= vAlpha[0];
	EmitVertex();

	gl_Position = pvmMatrix * ( vWorldPosition[0] + vec4(X, 0) + vec4(Y, 0) );
	gUV		= vec2( 0, 1 );
	gAlpha	= vAlpha[0];
	EmitVertex();

	gl_Position = pvmMatrix * ( vWorldPosition[0] - vec4(X, 0) - vec4(Y, 0) );
	gUV		= vec2( 1, 0 );
	gAlpha	= vAlpha[0];
	EmitVertex();

	gl_Position = pvmMatrix * ( vWorldPosition[0] + vec4(X, 0) - vec4(Y, 0) );
	gUV		= vec2( 0, 0 );
	gAlpha	= vAlpha[0];
	EmitVertex();

	EndPrimitive();
}