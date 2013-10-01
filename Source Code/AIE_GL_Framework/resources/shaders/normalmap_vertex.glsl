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

	vNormal		= normalize( Model * Normal).xyz;
	vTangent	= normalize( Model * vec4(Tangent.xyz,0)).xyz;
	vBiNormal	= normalize( Model * BiNormal ).xyz;

	vec4 pos = Position;

	vSurfacePos = pos;

	gl_Position = Projection * View * Model * pos;
}
