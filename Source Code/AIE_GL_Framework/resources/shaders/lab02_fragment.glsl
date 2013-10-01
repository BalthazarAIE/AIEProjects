#version 400

in vec4 gWorldPosition;
in vec4 gPosition;
in vec2 gUV;
in vec4 gCol;

out vec4 outColour;

uniform float Time;
uniform float Distance;
uniform sampler2D diffuseTexture;
uniform sampler2D secondaryTexture;
uniform vec4 Colour;

void main()
{
	outColour.rgba = texture2D( diffuseTexture, gUV ).bgra;
	outColour.rgb -= Colour.rgb;

	float dist = Distance;
	if( dist < 50 )
		outColour.rgba = texture2D( secondaryTexture, gUV ).bgra;

	else if( dist < 90 )
	{
		dist = (dist - 50)/ 40;
		outColour.rgba = texture2D( diffuseTexture, gUV ).bgra * dist;
		outColour.rgba += texture2D( secondaryTexture, gUV ).bgra * (1 - dist);
		outColour.rgb -= (Colour.rgb * dist);
	}
}