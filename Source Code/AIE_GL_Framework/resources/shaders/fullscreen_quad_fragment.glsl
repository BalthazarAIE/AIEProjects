#version 400

in vec4 vScreenPosition;
in vec2 vUV;

out vec4 outColour;

uniform sampler2D SceneTexture;
uniform sampler2D SecondaryTexture;

void main()
{  
	outColour.rgba = texture2D( SecondaryTexture, vUV ).rgba;
	//outColour.rgba += texture2D( SecondaryTexture, vUV ).rgba;
   //outColour.r = 1;

}