#version 400

in vec2 vUV;
out vec4 outColour;

uniform sampler2D	RenderBuffer;
uniform int			PassNumber;

float	fPixelWidth	= 1/1280.0;
float	fPixelHeight = 1/720.0;

void HorizontalGaussianPass( float a_fDepth );
void VerticalGaussianPass( float a_fDepth );

void main()
{
	////	Return normal Texture	////
	//outColour.rgba = texture2D( RenderBuffer, vUV ).rgba;

	float fDepth = texture2D( RenderBuffer, vUV ).a;
	fDepth = gl_FragCoord.z;
	fDepth =  0;

	if( PassNumber == 1 )
		HorizontalGaussianPass( fDepth );
	if( PassNumber == 2 )
		VerticalGaussianPass( fDepth );
}

void HorizontalGaussianPass( float a_fDepth )
{
	//a_fDepth *= 1000;
	//a_fDepth /= 100;
	//a_fDepth -= 0.5;

	//a_fDepth = clamp( a_fDepth, 0.0, 2);

	a_fDepth = 1 - a_fDepth;
	//if( a_fDepth > 0.9 )
	//	a_fDepth = 0.9;

	float fourAway	= 0;
	float threeAway = 0;
	float twoAway	= 0;
	float oneAway	= 0;
	float middle	= 1;

	middle		-= 0.84 * a_fDepth;
	oneAway		+= 0.15 * a_fDepth;
	twoAway		+= 0.12 * a_fDepth;
	threeAway	+= 0.09 * a_fDepth;
	fourAway	+= 0.05 * a_fDepth;

	vec4 sum = vec4(0.0);

	sum += texture2D( RenderBuffer, vec2(vUV.x - fPixelWidth*4.0, vUV.y) ) * fourAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x - fPixelWidth*3.0, vUV.y) ) * threeAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x - fPixelWidth*2.0, vUV.y) ) * twoAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x - fPixelWidth, vUV.y) ) * oneAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y) ) * middle;
	sum += texture2D( RenderBuffer, vec2(vUV.x + fPixelWidth, vUV.y) ) * oneAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x + fPixelWidth*2.0, vUV.y) ) * twoAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x + fPixelWidth*3.0, vUV.y) ) * threeAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x + fPixelWidth*4.0, vUV.y) ) * fourAway;

	outColour = sum;
}

void VerticalGaussianPass( float a_fDepth )
{
	//a_fDepth *= 1000;
	//a_fDepth /= 100;
	//a_fDepth -= 0.5;

	//a_fDepth = clamp( a_fDepth, 0.0, 2);
	a_fDepth = 1 - a_fDepth;
	//if( a_fDepth > 0.9 )
	//	a_fDepth = 0.9;
	

	float fourAway	= 0;
	float threeAway = 0;
	float twoAway	= 0;
	float oneAway	= 0;
	float middle	= 1;

	middle		-= 0.84 * a_fDepth;
	oneAway		+= 0.15 * a_fDepth;
	twoAway		+= 0.12 * a_fDepth;
	threeAway	+= 0.09 * a_fDepth;
	fourAway	+= 0.05 * a_fDepth;

	vec4 sum = vec4(0.0);

	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y - fPixelHeight*4.0) ) * fourAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y - fPixelHeight*3.0) ) * threeAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y - fPixelHeight*2.0) ) * twoAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y - fPixelHeight) ) * oneAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y) ) * middle;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y + fPixelHeight) ) * oneAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y + fPixelHeight*2.0) ) * twoAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y + fPixelHeight*3.0) ) * threeAway;
	sum += texture2D( RenderBuffer, vec2(vUV.x, vUV.y + fPixelHeight*4.0) ) * fourAway;

	outColour = sum;
}