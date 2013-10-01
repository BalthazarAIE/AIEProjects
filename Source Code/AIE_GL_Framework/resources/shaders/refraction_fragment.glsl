#version 400

in vec4 gWorldPosition;
in vec4 gScreenPosition;
in vec2 gUV;
in vec4 gCol;

out vec4 outColour;

uniform sampler2D Texture;
uniform sampler2D SceneTexture;
uniform sampler2D WaterBumpMap;
uniform float Time;

void main()
{
	vec2 scale = vec2(0.05,0.05);

	vec4 bumpTex = 2.0 * texture2D( WaterBumpMap, gUV ) - 1.0;

	vec2 newUV = (gScreenPosition.xy/gScreenPosition.w) + (bumpTex.xy * scale.xy);
	//vec2 newUV = (gScreenPosition.xy/gScreenPosition.w);

	newUV.x = (newUV.x + 1) * 0.5;
	newUV.y = (newUV.y + 1) * 0.5;

	if( newUV.x > 1.0 )
		newUV.x = 1.0;
   
	//outColour.rgba = texture2D( Texture, gUV ).bgra;
	outColour.rgba = texture2D( SceneTexture, newUV ).rgba;
	outColour.b += 0.1;
	outColour.a = 1;

}
