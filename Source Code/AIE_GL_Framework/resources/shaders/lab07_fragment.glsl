#version 400

in vec4 gWorldPosition;
in vec4 gScreenPosition;
in vec2 gUV;
in vec4 gCol;
in vec4 gNormal;

out vec4 outColour;

uniform mat4 View;
uniform sampler2D diffuseTexture;
uniform vec4 Colour;

void main()
{
	vec4 norm = normalize( gNormal );

	vec4 lightDir1 = vec4( 4, 1, 0, 0 );
	lightDir1 = normalize( lightDir1 );
	vec4 lightColour1 = vec4(1,1,1,1);
	vec4 halfVec1 = View[3] - lightDir1;
	halfVec1 = normalize( halfVec1 );

	vec4 lightDir2 = vec4( -5, -2, 1, 0 );
	lightDir2 = normalize( lightDir2 );
	vec4 lightColour2 = vec4(0.1,0.1,0.1,1);
	vec4 halfVec2 = View[3] - lightDir2;
	halfVec2 = normalize( halfVec2 );

	outColour.rgba = texture2D( diffuseTexture, gUV ).bgra;
	outColour += Colour;

	outColour.rgb *= lightColour1.rgb * max(dot( norm.xyz, normalize(lightDir1.xyz) ),0);
	outColour.rgb += lightColour2.rgb * max(dot( norm.xyz, normalize(lightDir2.xyz) ),0);

	
}