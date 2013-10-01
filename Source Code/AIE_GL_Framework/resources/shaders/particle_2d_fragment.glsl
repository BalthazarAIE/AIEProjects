#version 400

in vec2 gUV;
in float gAlpha;

out vec4 outColour;

uniform sampler2D diffuseTexture;
uniform sampler2D renderBuffer;

void main()
{
	outColour.bgra = texture2D( diffuseTexture, gUV ).rgba;
	//if( outColour.a > gAlpha )
		//outColour.r *= 5;
		outColour.a *= gAlpha;
		//outColour.a = gl_FragCoord.z * gl_FragCoord.w;
}
