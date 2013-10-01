#version 400

in vec4 gWorldPosition;
in vec4 gPosition;
in vec2 gUV;
in vec4 gCol;

out vec4 outColour;

uniform sampler2D diffuseTexture;

void main()
{
		outColour.rgba = texture2D( diffuseTexture, gUV ).bgra;
}