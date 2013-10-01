#version 400

// very simple vertex shader that just transforms an object-space
// position into clip space and passes along a texture coordinate

in vec4 Position;
in vec4 Normal;
in vec4 Tangent;
in vec4 BiNormal;
in vec4 Indices;
in vec4 Weights;
in vec2 UV;

out vec3 vNormal;
out vec3 vTangent;
out vec3 vBiNormal;
out vec2 vUV;
out vec4 vCameraPos;
out vec4 vSurfacePos;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform vec4 CamPos;

uniform mat4 boneArray[73];

void main()
{
	vUV = UV;

	vec4 norm	= normalize( Model * Normal);
	vTangent	= normalize( Model * vec4(Tangent.xyz,0)).xyz;
	vBiNormal	= normalize( Model * BiNormal ).xyz;

	mat4 bone1 = boneArray[ int(Indices[0]) ];
	mat4 bone2 = boneArray[ int(Indices[1]) ];
	mat4 bone3 = boneArray[ int(Indices[2]) ];
	mat4 bone4 = boneArray[ int(Indices[3]) ];

	vec4 pos;
	pos =  (Position * bone1) * Weights[0];
	pos += (Position * bone2) * Weights[1];
	pos += (Position * bone3) * Weights[2];
	pos += (Position * bone4) * Weights[3];

	vNormal = (norm * bone1).xyz;

	vSurfacePos = pos;

	gl_Position = Projection * View * Model * pos;
}
