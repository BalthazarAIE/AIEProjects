#version 330

in vec2 vUV;

out vec4 outColour;

uniform sampler2D renderBuffer;
uniform float Time;

void EdgeDetection();
void CartoonGlow();
void VerticalGaussianPass( float a_fDepth );

float	pixelWidth = 1/1280.0;
float	pixelHeight = 1/720.0;

void main()
{

	////	Return normal Texture	////
	outColour.rgba = texture2D( renderBuffer, vUV ).rgba;
	float depth = texture2D( renderBuffer, vUV ).a;

	//CartoonGlow();

	//if( depth < 0.2 )
		VerticalGaussianPass( depth );

	outColour.a = depth;

	//EdgeDetection();
}

void EdgeDetection()
{
	///////////////////////////
	//	Sobel operator
	///////////////////////////
	float	X = 0;
	float	Y = 0;
	X += texture2D( renderBuffer, vec2(vUV.x-pixelWidth, vUV.y-pixelHeight)).a * -1;
	X += texture2D( renderBuffer, vec2(vUV.x-pixelWidth, vUV.y)).a * -2;
	X += texture2D( renderBuffer, vec2(vUV.x-pixelWidth, vUV.y+pixelHeight)).a * -1;
	X += texture2D( renderBuffer, vec2(vUV.x+pixelWidth, vUV.y-pixelHeight)).a * 1;
	X += texture2D( renderBuffer, vec2(vUV.x+pixelWidth, vUV.y)).a * 2;
	X += texture2D( renderBuffer, vec2(vUV.x+pixelWidth, vUV.y+pixelHeight)).a * 1;

	Y += texture2D( renderBuffer, vec2(vUV.x-pixelWidth, vUV.y-pixelHeight)).a * -1;
	Y += texture2D( renderBuffer, vec2(vUV.x, vUV.y-pixelHeight)).a * -2;
	Y += texture2D( renderBuffer, vec2(vUV.x+pixelWidth, vUV.y-pixelHeight)).a * -1;
	Y += texture2D( renderBuffer, vec2(vUV.x-pixelWidth, vUV.y+pixelHeight)).a * 1;
	Y += texture2D( renderBuffer, vec2(vUV.x, vUV.y+pixelHeight)).a * 2 ;
	Y += texture2D( renderBuffer, vec2(vUV.x+pixelWidth, vUV.y+pixelHeight)).a * 1 ;

	float redPixel = sqrt( X*X + Y*Y );

	if( redPixel > 0.08 )
		outColour.rgba = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	else
		outColour.rgba += vec4( 0.0f, 0.0f, 0.0f, 0.0f );
}

void CartoonGlow()
{
	vec4	pixel = vec4( texture2D( renderBuffer, vUV ) );
	float	glow = 8.0 * ((pixelWidth + pixelHeight) / 2.0);
	vec4	bloom = vec4(0);
	int		count = 0;

	for( float x = vUV.x - glow; x < vUV.x + glow; x += pixelWidth )
	{
		for( float y = vUV.y - glow; y < vUV.y + glow; y += pixelHeight )
		{
			vec4 thatCol = texture2D( renderBuffer, vec2(x,y) );
			float sumpixel = 0;
			sumpixel += abs(pixel.r - thatCol.r);
			sumpixel += abs(pixel.g - thatCol.g);
			sumpixel += abs(pixel.b - thatCol.b);

			if( sumpixel < 0.1 )
			{
				bloom += (texture2D( renderBuffer, vec2(x,y) ) - 0.3) * 250.0;
				count++;
			}
		}
	}

	bloom = clamp(bloom/(count*30), 0.0, 1.0);
	outColour.rgba = pixel + bloom;
}

void VerticalGaussianPass( float a_fDepth )
{
	//a_fDepth *= 1000;
	//a_fDepth /= 100;
	//a_fDepth -= 0.5;

	//a_fDepth = clamp( a_fDepth, 0.0, 2);
	a_fDepth = 1 - a_fDepth;
	if( a_fDepth > 0.5 )
		a_fDepth = 0.5;
	

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

	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y - pixelHeight*4.0) ) * fourAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y - pixelHeight*3.0) ) * threeAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y - pixelHeight*2.0) ) * twoAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y - pixelHeight) ) * oneAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y) ) * middle;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y + pixelHeight) ) * oneAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y + pixelHeight*2.0) ) * twoAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y + pixelHeight*3.0) ) * threeAway;
	sum += texture2D( renderBuffer, vec2(vUV.x, vUV.y + pixelHeight*4.0) ) * fourAway;

	outColour = sum;
}