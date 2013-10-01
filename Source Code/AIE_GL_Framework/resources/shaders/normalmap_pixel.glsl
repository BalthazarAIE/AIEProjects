#version 400

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
uniform vec4 ambientColour;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform vec4 CamPos;

uniform float time;

// directional light
uniform vec4 dirLightDir;
uniform vec4 dirLightCol;

// point light
uniform vec4 pointLightPos;
uniform vec4 pointLightCol;

// spot light
uniform vec4 spotLightPos;
uniform vec4 spotLightDir;
uniform vec4 spotLightCol;

void main()
{
	// sample normal map and convert values from 0.0-1.0 colour to -1.0-1.0 spherical
	vec3 normal = texture2D(normalTexture, vUV).rgb * 2 - 1;

	// build tangent basis matrix and convert texture normal to correct space
	mat3 TBN = mat3(vTangent,vBiNormal,vNormal);
	normal = normalize(TBN * normal);

	//Specular texture
	vec3 SpecTexture	= texture2D(specularTexture, vUV).rgb;

	vec3 material		= materialDiffuse.rgb;

//------------------------------//
//		AMBIENT LIGHTING		//
//------------------------------//
	outColour.rgb = ambientColour.rgb * 0.1;

//------------------------------//
//		DIRECTIONAL LIGHT		//
//------------------------------//

//===Diffuse Lighting===//
	outColour.rgb += texture2D(diffuseTexture, vUV).rgb * material * dirLightCol.rgb * max(dot( normal, normalize(dirLightDir.xyz) ),0);

//===Specular Lighting===//
	vec3 R			= (2 * normal * dot(normalize(dirLightDir.rgb), normal) - normalize(dirLightDir.rgb) ); //Light's reflection vector
	vec3 V			= normalize( CamPos.xyz - vSurfacePos.xyz ); //Vector from surface to camera
	float RdotV		= clamp( dot(R, V), 0, 1 );
	outColour.rgb	+= SpecTexture * pow(RdotV, 20) * dirLightCol.rgb;

//------------------------------//
//		POINT LIGHT				//
//------------------------------//
	
	vec4 pointLightDir = vSurfacePos - pointLightPos;
	pointLightDir = normalize( pointLightDir );

	//===Diffuse Lighting===//
	vec3 diffTerm = texture2D(diffuseTexture, vUV).rgb * material * pointLightCol.rgb * max(dot( normal, normalize(pointLightDir.xyz) ),0);

	//===Specular Lighting===//
	R				= (2 * normal * dot(normalize(pointLightDir.rgb), normal) - normalize(pointLightDir.rgb) ); //Light's reflection vector
	V				= normalize( CamPos.xyz - vSurfacePos.xyz ); //Vector from surface to camera
	RdotV			= clamp( dot(R, V), 0, 1 );
	vec3 specTerm	= SpecTexture * pow(RdotV, 20) * pointLightCol.rgb;

	//===Attenuation Calculation===//
	vec4 dist			= vSurfacePos - pointLightPos;
	float d				= length(dist);
	float constAttn		= 1.0;
	float linAttn		= 0.01;
	float quadAttn		= 0.01;
	float attenuation	= 1.0 / (	constAttn +
									(linAttn * d) + 
									(quadAttn * d * d) );

	outColour.rgb += (diffTerm + specTerm) * attenuation;

//------------------------------//
//		SPOT LIGHT				//
//------------------------------//

	vec3 lightDir = spotLightPos.xyz - vSurfacePos.xyz;
	d = length(lightDir);
	float NdotL = max( dot(vNormal, normalize(lightDir)), 0 );
	//if(NdotL > 0 )
	//{
		float spotEffect = dot( normalize(spotLightDir.xyz), normalize(-lightDir) );
		if( spotEffect > 0.8 )
		{
			spotEffect = pow( spotEffect, 0.1 );
			attenuation	= spotEffect / (	constAttn +
											(linAttn * d) + 
											(quadAttn * d * d) );

			attenuation = 1;

			//===Diffuse Lighting===//
			diffTerm = texture2D(diffuseTexture, vUV).rgb * material * spotLightCol.rgb * max(dot( normal, normalize(spotLightDir.xyz) ),0);

			//===Specular Lighting===//
			R				= (2 * normal * dot(normalize(spotLightDir.rgb), normal) - normalize(spotLightDir.rgb) ); //Light's reflection vector
			V				= normalize( CamPos.xyz - vSurfacePos.xyz ); //Vector from surface to camera
			RdotV			= clamp( dot(R, V), 0, 1 );
			specTerm		= SpecTexture * pow(RdotV, 20) * spotLightCol.rgb;

			outColour.rgb	+= (diffTerm + specTerm) * attenuation;
		}
	//}

	outColour.a = 1;
}