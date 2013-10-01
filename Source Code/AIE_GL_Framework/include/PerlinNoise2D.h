#ifndef _PERLINNOISE2D_H_
#define _PERLINNOISE2D_H_

#include <cmath>

float CosInterpolate( float a, float b, float t )
{
	float ft = t * 3.1415927f;
	float f = (1 - cos(ft)) * 0.5f;

	return a*(1-f) + b*f;
}

float Noise(int x, int y)
{
	int n = x + y * 57;
	n = (n<<13) ^ n;
	
	//return ( 1.0 - ( (n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0 );
	return ( 1.0f - ( (n*(n*n*15485863 + 982451653) + 899809343) & 0x7fffffff) / 1073741824.0f );
	//return ( 1.0 - ( (n*(n*n*1039 + 151) + 1039) & 0x7fffffff) / 1073741824.0 );
	//return ( 1.0 - ( (n*(n*n*7919 + 7919) + 7919) & 0x7fffffff) / 1073741824.0 );
}

float SmoothedNoise(float fX, float fY)
{
	int x = static_cast<int>(fX);
	int y = static_cast<int>(fY);

	float corners	= ( Noise(x-1,y-1) + Noise(x+1,y-1) + Noise(x-1,y+1) + Noise(x+1,y+1) ) / 16;
	float sides		= ( Noise(x-1,y) + Noise(x+1,y) + Noise(x,y-1) + Noise(x,y+1) ) / 8;
	float centre	= Noise(x,y) / 4;

	return corners + sides + centre;
}

float InterpolatedNoise(float x, float y)
{
	int		intX	= (int)x;
	float	fracX	= x - intX;

	int		intY	= (int)y;
	float	fracY	= y - intY;

	float v1 = SmoothedNoise( (float)intX,		(float)intY	);
	float v2 = SmoothedNoise( (float)intX+1,	(float)intY	);
	float v3 = SmoothedNoise( (float)intX,		(float)intY+1	);
	float v4 = SmoothedNoise( (float)intX+1,	(float)intY+1	);

	float i1 = CosInterpolate(v1, v2, fracX);
	float i2 = CosInterpolate(v3, v4, fracX);

	return CosInterpolate(i1, i2, fracY);
}

float PerlinNoise2D( float x, float y, float persistence, int numOctaves )
{
	float total = 0;

	for( int i = 0; i < numOctaves; ++i )
	{
		float	frequency = pow( 2.0f, i );
		float	amplitude = pow( persistence, i );

		total = total + InterpolatedNoise( x*frequency, y*frequency) * amplitude;
	}

	return total;
}

#endif