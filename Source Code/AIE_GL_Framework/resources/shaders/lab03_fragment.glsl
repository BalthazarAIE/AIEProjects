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
   outColour.rgba = texture2D( diffuseTexture, gUV ).bgra;
   outColour.rgba = vec4(0.8,0.6,0.2,1);

   outColour.rgba += vec4(0.2,1,0.3, 0.3)	* max(dot( gNormal.xyzw, vec4(0,1,0,1) ),0);
   outColour.rgba += vec4(1,0.2,0.3, 0.3)	* max(dot( gNormal.xyzw, vec4(0,-1,0,1) ),0);
   outColour.rgba += vec4(0,0,0.6, 0.3)		* max(dot( gNormal.xyzw, vec4(1,0,0,1) ),0);
}