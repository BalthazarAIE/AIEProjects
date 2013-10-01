#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Utilities.h"

union PSize{
	struct{ float width, height;	};
	struct{ AIE::vec2 size;			};
};

struct ParticleVertex
{
	union
	{
		struct{	AIE::vec4 position;	};
		struct{ float x, y, z, w;	};
	};

	bool operator == (const ParticleVertex& rhs)
	{
		return ( x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w );
	}
};

struct Particle
{
	AIE::vec4	vPosition;
	PSize		oSize;
	float		fAlpha;
	AIE::vec4	vOldPosition;
	AIE::vec4	vVelocity;
	AIE::vec4	vColour;
	float		fEnergy;
	bool		bIsDead;
};

#endif