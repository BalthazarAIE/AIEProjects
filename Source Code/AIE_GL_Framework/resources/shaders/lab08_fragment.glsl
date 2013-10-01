#version 400

in vec4 gWorldPosition;
in vec4 gPosition;
in vec2 gUV;
in vec4 gCol;
in vec4 gNormal;

out vec4 outColour;

uniform sampler2D diffuseTexture;

void main()
{
	//float yPos = (gWorldPosition.y * 0.005) + 0.5;
	//outColour.rgb = vec3(yPos, yPos, yPos);
	vec4 lightCol;
	lightCol.r = 0.33;
	lightCol.b = 0.13;
	lightCol.g = 0.02;
	lightCol.a = 1.0;

	vec2 uv;
	uv.x =  (gWorldPosition.x / 10) /20 ;
	uv.y =  (gWorldPosition.z / 10) /20 ;
	
    outColour.rgba = texture2D( diffuseTexture, uv ).bgra;
	outColour += lightCol;

	vec4 lightDir = vec4( 5, 5, 1, 0);
	lightDir = normalize( lightDir );

	vec4 lightColour = vec4(1,1,1,1);

	outColour.rgb *= lightColour.rgb * max(dot( gNormal.xyz, normalize(lightDir.xyz) ),0);

	outColour.a = 1;
}