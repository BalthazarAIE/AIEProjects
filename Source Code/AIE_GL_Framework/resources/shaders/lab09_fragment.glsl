#version 330

in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiNormal;
in vec4 Indices;
in vec4 Weights;
in vec2 vUV;
in vec4 vCameraPos;
in vec4 vSurfacePos;

out vec4 outColour;

uniform vec4 materialDiffuse;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform vec4 CamPos;

// directional light
uniform vec4 light0Dir;
uniform vec4 light0Colour;

void main()
{
	// sample normal map and convert values from 0.0-1.0 colour to -1.0-1.0 spherical
	//vec3 normal = texture2D(normalTexture, vUV).rgb * 2 - 1;

	// build tangent basis matrix and convert texture normal to correct space
	//mat3 TBN = mat3(vTangent,vBiNormal,vNormal);
	//normal = normalize(TBN * normal);


vec3 vAmbientCol	= vec3(0.9,0.1,0.1);
vec3 lightCol		= vec3(1,1,1);
vec3 lightDir0		= vec3(0,0,1);
lightDir0			= normalize( lightDir0 );

//------------------------------//
//		AMBIENT LIGHTING		//
//------------------------------//
	outColour.rgb = vAmbientCol * 0.1;

//------------------------------//
//		DIFFUSE LIGHTING		//
//------------------------------//
	vec3 material = vec3(1,0,0);
	
	// sample diffuse and tint based on lighting
	outColour.rgb += material * lightCol * max(dot( vNormal, normalize(lightDir0) ),0);

//------------------------------//
//		SPECULAR LIGHTING		//
//------------------------------//
	//Light's reflection vector
	vec3 R = (2 * vNormal * dot(normalize(lightDir0), vNormal) - normalize(lightDir0) );

	//Vector from surface to camera
	vec3 V = normalize( CamPos.xyz - vSurfacePos.xyz );
	float RdotV = clamp( dot(R, V), 0, 1 );
	outColour.rgb += pow(RdotV, 20) * lightCol;

	outColour.a = 1;
}
