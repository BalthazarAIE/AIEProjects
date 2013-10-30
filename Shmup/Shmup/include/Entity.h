#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Vector2.h"
#include "AIE.h"
#include "Sprite.h"
#include "Globals.h"


typedef float xp;

class Entity:
	public Sprite
{
public:
	Entity(void);
	Entity(float a_fXPos,float a_fYPos,float a_fXVel,float a_fYVel);
	Entity(float a_fXPos,float a_fYPos);
	Entity(Vector2 a_vPos,Vector2 a_vVel);
	Entity(Vector2 a_vPos);
	~Entity(void);

	
	void Update();

	xp Kill();
	void Respawn();
	void Respawn(Vector2 a_vPos,Vector2 a_vVel);
	bool isAlive();
	void ApplyDamage(float a_fDam);
	bool CollisionCheck(Entity *other);
	bool CollisionCheck(Vector2&,Vector2&);
	float GetRadius();
	void SetRadius(float a_fRadius);
	void SetXp(xp );
	
private:
	float m_fHealth;
	bool m_bisAlive;
	xp m_xExperiance;
	float m_fCollisionRadius;
};
#endif
