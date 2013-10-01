#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 26) out;

in vec4 vWorldPosition[];
in vec4 vScreenPosition[];
in vec2 vSize[];
in vec4 vColour[];
in float vAlpha[];

out vec2 gUV;
out vec4 gColour;
out float gAlpha;
out vec3 gNormal;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 CameraMat;

uniform float Time;

void main()
{
	vec2 halfSize	= vSize[0] * 0.5f;
	mat4 pvmMatrix	= Projection * View * Model;

	float X		= halfSize.x;
	float Y		= halfSize.y;
	float Z		= halfSize.y;

	//float val = vSize.x * vSize.y;

	float val = Time / 3.14159;
	float t = Time - val;

	float angle = sin(t);
	//angle *= gAlpha;
	mat4 rotMat1;
	rotMat1[0] = vec4( cos(t*Z), -sin(t*Z), 0, 0 );
	rotMat1[1] = vec4( sin(t*Z), cos(t*Z), 0, 0 );
	rotMat1[2] = vec4( 0, 0, 1, 0 );
	rotMat1[3] = vec4( 0, 0, 0, 1 );

	mat4 rotMat2;
	rotMat2[0] = vec4( 1, 0, 0, 0 );
	rotMat2[1] = vec4( 0, cos(t*X), -sin(t*X), 0 );
	rotMat2[2] = vec4( 0, sin(t*X), cos(t*X), 0 );
	rotMat2[3] = vec4( 0, 0, 0, 1 );

	mat4 rotMat3;
	rotMat3[0] = vec4( cos(t*Y), 0, sin(t*Y), 0 );
	rotMat3[1] = vec4( 0, 1, 0, 0 );
	rotMat3[2] = vec4( -sin(t*Y), 0, cos(t*Y), 0 );
	rotMat3[3] = vec4( 0, 0, 0, 1 );

	mat4 rotMat = rotMat3 * rotMat2 * rotMat3;

	/////////////////////
	//Front Face
	/////////////////////

	vec4 front1 = vWorldPosition[0] + vec4( -X, -Y, Z, 0 ) * rotMat;
	vec4 front2 = vWorldPosition[0] + vec4( X, -Y, Z, 0 ) * rotMat;
	vec4 front3 = vWorldPosition[0] + vec4( -X, Y, Z, 0 ) * rotMat;
	vec4 front4 = vWorldPosition[0] + vec4( X, Y, Z, 0 ) * rotMat;

	vec3 frontNorm = cross(	front1.xyz - front2.xyz,
							front3.xyz - front1.xyz	);
	frontNorm = normalize( frontNorm );

	gl_Position = pvmMatrix * front1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = frontNorm;
	EmitVertex();

	gl_Position = pvmMatrix * front2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = frontNorm;
	EmitVertex();

	gl_Position = pvmMatrix * front3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = frontNorm;
	EmitVertex();

	gl_Position = pvmMatrix * front4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = frontNorm;
	EmitVertex();

	/////////////////////
	//Right face
	/////////////////////

	vec4 right1 = vWorldPosition[0] + vec4( X, Y, Z, 0 ) * rotMat;
	vec4 right2 = vWorldPosition[0] + vec4( X, -Y, Z, 0 ) * rotMat;
	vec4 right3 = vWorldPosition[0] + vec4( X, Y, -Z, 0 ) * rotMat;
	vec4 right4 = vWorldPosition[0] + vec4( X, -Y, -Z, 0 ) * rotMat;

	vec3 rightNorm = cross(	right1.xyz - right2.xyz,
							right3.xyz - right1.xyz	);
	rightNorm = normalize( rightNorm );

	gl_Position = pvmMatrix * right1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = rightNorm;
	EmitVertex();

	gl_Position = pvmMatrix * right2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = rightNorm;
	EmitVertex();

	gl_Position = pvmMatrix * right3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = rightNorm;
	EmitVertex();

	gl_Position = pvmMatrix * right4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = rightNorm;
	EmitVertex();

	/////////////////////
	//Back face
	/////////////////////

	vec4 back1 = vWorldPosition[0] + vec4( X, -Y, -Z, 0 ) * rotMat;
	vec4 back2 = vWorldPosition[0] + vec4( -X, -Y, -Z, 0 ) * rotMat;
	vec4 back3 = vWorldPosition[0] + vec4( X, Y, -Z, 0 ) * rotMat;
	vec4 back4 = vWorldPosition[0] + vec4( -X, Y, -Z, 0 ) * rotMat;

	vec3 backNorm = cross(	back1.xyz - back2.xyz,
							back3.xyz - back1.xyz	);
	backNorm = normalize( backNorm );

	gl_Position = pvmMatrix * back1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = backNorm;
	EmitVertex();

	gl_Position = pvmMatrix * back2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = backNorm;
	EmitVertex();

	gl_Position = pvmMatrix * back3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = backNorm;
	EmitVertex();

	gl_Position = pvmMatrix * back4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = backNorm;
	EmitVertex();

	/////////////////////
	//Left face
	/////////////////////

	vec4 left1 = vWorldPosition[0] + vec4( -X, Y, -Z, 0 ) * rotMat;
	vec4 left2 = vWorldPosition[0] + vec4( -X, -Y, -Z, 0 ) * rotMat;
	vec4 left3 = vWorldPosition[0] + vec4( -X, Y, Z, 0 ) * rotMat;
	vec4 left4 = vWorldPosition[0] + vec4( -X, -Y, Z, 0 ) * rotMat;

	vec3 leftNorm = cross(	left1.xyz - left2.xyz,
							left3.xyz - left1.xyz	);
	leftNorm = normalize( leftNorm );

	gl_Position = pvmMatrix * left1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = leftNorm;
	EmitVertex();

	gl_Position = pvmMatrix * left2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = leftNorm;
	EmitVertex();

	gl_Position = pvmMatrix * left3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = leftNorm;
	EmitVertex();

	gl_Position = pvmMatrix * left4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = leftNorm;
	EmitVertex();

	/////////////////////
	//Bottom face
	/////////////////////

	vec4 bottom1 = vWorldPosition[0] + vec4( -X, -Y, Z, 0 ) * rotMat;
	vec4 bottom2 = vWorldPosition[0] + vec4( -X, -Y, -Z, 0 ) * rotMat;
	vec4 bottom3 = vWorldPosition[0] + vec4( X, -Y, Z, 0 ) * rotMat;
	vec4 bottom4 = vWorldPosition[0] + vec4( X, -Y, -Z, 0 ) * rotMat;

	vec3 bottomNorm = cross(	bottom1.xyz - bottom2.xyz,
								bottom3.xyz - bottom1.xyz	);
	bottomNorm = normalize( bottomNorm );
	gl_Position = pvmMatrix * bottom1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = bottomNorm;
	EmitVertex();

	gl_Position = pvmMatrix * bottom2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = bottomNorm;
	EmitVertex();

	gl_Position = pvmMatrix * bottom3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = bottomNorm;
	EmitVertex();

	gl_Position = pvmMatrix * bottom4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = bottomNorm;
	EmitVertex();

	/////////////////////
	//Move to top
	/////////////////////
	gl_Position = pvmMatrix * ( vWorldPosition[0] + vec4( X, -Y, -Z, 0 )  * rotMat);
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	EmitVertex();

	gl_Position = pvmMatrix * ( vWorldPosition[0] + vec4( -X, Y, Z, 0 )  * rotMat);
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	EmitVertex();

	/////////////////////
	//Top face
	/////////////////////

	vec4 top1 = vWorldPosition[0] + vec4( -X, Y, Z, 0 ) * rotMat;
	vec4 top2 = vWorldPosition[0] + vec4( X, Y, Z, 0 ) * rotMat;
	vec4 top3 = vWorldPosition[0] + vec4( -X, Y, -Z, 0 ) * rotMat;
	vec4 top4 = vWorldPosition[0] + vec4( X, Y, -Z, 0 ) * rotMat;

	vec3 topNorm = cross(	top1.xyz - top2.xyz,
							top3.xyz - top1.xyz	);
	topNorm = normalize( topNorm );

	gl_Position = pvmMatrix * top1;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = topNorm;
	EmitVertex();

	gl_Position = pvmMatrix * top2;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = topNorm;
	EmitVertex();

	gl_Position = pvmMatrix * top3;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = topNorm;
	EmitVertex();

	gl_Position = pvmMatrix * top4;
	gAlpha	= vAlpha[0];
	gColour = vColour[0];
	gNormal = topNorm;
	EmitVertex();

	EndPrimitive();
}