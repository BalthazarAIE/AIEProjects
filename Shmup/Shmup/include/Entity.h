#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Vector2.h"
#include "AIE.h"
#include "Sprite.h"
#include "Globals.h"
#include "CircleCollider.h"


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
	void ApplyDamage(float a_fDam);

	inline bool isAlive(){return m_bisAlive;}
	inline void SetXp(xp exp){m_xExperiance = exp;}
	inline CircleCollider& GetCollider(){return m_oCollider;}
	
private:
	float m_fHealth;
	bool m_bisAlive;
	xp m_xExperiance;
	CircleCollider m_oCollider;
};
#endif
