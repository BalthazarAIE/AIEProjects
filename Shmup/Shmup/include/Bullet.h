#ifndef _BULLET_H_
#define _BULLET_H_
#include "Entity.h"


class Bullet :
	public Entity
{
public:
	Bullet(void);
	Bullet(const Bullet &bill);
	~Bullet(void);
	void Fire(Vector2 a_vPos,Vector2 a_vVel);

};
#endif
