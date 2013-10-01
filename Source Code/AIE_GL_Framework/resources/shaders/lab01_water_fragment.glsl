#version 400

// very simple pixel shader that just samples a texture

in vec4 gWorldPosition;
in vec4 gPosition;
in vec2 gUV;
in vec4 gCol;

out vec4 outColour;

uniform sampler2D diffuseTexture;

void main()
{
   outColour.rgba = texture2D( diffuseTexture, gUV ).bgra;

   //outColour.r += gWorldPosition.y;
	
	outColour.rgba += vec4( 0.87, 0.1, 0.26, 1.0 ) * (gWorldPosition.y - 0.5)/2;
	outColour.a = 0.2;
	//outColour.a = gl_FragCoord.z * gl_FragCoord.w;
}