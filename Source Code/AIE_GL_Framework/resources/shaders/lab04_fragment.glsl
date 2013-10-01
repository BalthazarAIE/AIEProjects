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
	if( gWorldPosition.y < 20 )
	{
		outColour.r = 0.2039;
		outColour.g = 0.4666;
		outColour.b = 0.8156;
	}
	else if( gWorldPosition.y >= 20 && gWorldPosition.y < 21.5 )
	{
		outColour.r = 0.8156;
		outColour.g = 0.7372;
		outColour.b = 0.2039;
	}
	else if( gWorldPosition.y >= 21.5 && gWorldPosition.y < 35 )
	{
		outColour.r = 0.2039;
		outColour.g = 0.8156;
		outColour.b = 0.2039;
	}
	else if( gWorldPosition.y >= 35 && gWorldPosition.y < 36  )
	{
		outColour.r = 0.8156;
		outColour.g = 0.4666;
		outColour.b = 0.2039;
	}
	else if( gWorldPosition.y >= 36 && gWorldPosition.y < 43  )
	{
		outColour.r = 0.6;
		outColour.g = 0.6;
		outColour.b = 0.4;
	}
	else if( gWorldPosition.y >= 43 )
	{
		outColour.r = 1;
		outColour.g = 1;
		outColour.b = 1;
	}
   //outColour.r = 1 - outColour.r;
   //outColour.g = 1 - outColour.g;
  // outColour.b = 1 - outColour.b;

  //outColour.rgb *= texture2D( diffuseTexture, gUV ).bgr;
	//outColour.rgb = vec3(1,0,0);
	outColour.a = 1.0;
}