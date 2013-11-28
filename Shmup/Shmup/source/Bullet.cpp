#include "Bullet.h"


Bullet::Bullet(void)
{
	Respawn(Vector2(-10,-10),Vector2(0,0));
	GetCollider().SetRadius(2);
	SetXp(0);
}
Bullet::Bullet(const Bullet &bill)
{
	
}

Bullet::~Bullet(void)
{
}

void Bullet::Fire(Vector2 a_vPos,Vector2 a_vVel)
{
	Respawn(a_vPos,a_vVel);
}