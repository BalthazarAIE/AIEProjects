#version 400

layout( triangles, equal_spacing, ccw ) in;

in vec4 tcWorldPosition[];
in vec2 tcUV[];

out vec4 teWorldPosition;
out vec2 teUV;

uniform sampler2D diffuseTexture;
uniform sampler2D displacementTexture;

void main()
{
	vec4 p0 = gl_in[ 0 ].gl_Position;
	vec4 p1 = gl_in[ 1 ].gl_Position;
	vec4 p2 = gl_in[ 2 ].gl_Position;
	vec3 p = gl_TessCoord.xyz;

	teUV = tcUV[0]*p.x + tcUV[1]*p.y + tcUV[2]*p.z;
	teWorldPosition = tcWorldPosition[0]*p.x + tcWorldPosition[1]*p.y + tcWorldPosition[2]*p.z;

	float disp	= texture2D( diffuseTexture, teUV ).r;
	float scale = 60;

	gl_Position = p0 * p.x + p1 * p.y + p2 * p.z;
	teWorldPosition.y += disp * scale;
}