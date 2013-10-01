#version 400

in vec2 gUV;
in vec4 gColour;
in float gAlpha;
in vec3 gNormal;

out vec4 outColour;

uniform sampler2D diffuseTexture;
uniform sampler2D renderBuffer;

uniform float Time;

void main()
{
	vec4 lightDir1 = vec4( 4, 1, 0, 0 );
	lightDir1 = normalize( lightDir1 );
	vec4 lightColour1 = vec4(1,1,1,1);

	vec4 lightDir2 = vec4( -5, -2, 1, 0 );
	lightDir2 = normalize( lightDir2 );
	vec4 lightColour2 = vec4(0.1,0.1,0.1,1);

	outColour.rgb = vec3(4,0,2);
	outColour.rgb += lightColour1.rgb * max(dot( gNormal.xyz, normalize(lightDir1.xyz) ),0);
	outColour.rgb += lightColour2.rgb * max(dot( gNormal.xyz, normalize(lightDir2.xyz) ),0);

	outColour.a = 1;
	//outColour.a *= gAlpha;
	//if( gAlpha < 0.1 )
	//	outColour.a = 0;
	outColour.a *= gAlpha;
}
