
#include "Entity.h"
#include "Vector2.h"



Entity::Entity(void)
{
	Sprite();
	GetCollider() = CircleCollider();
	m_bisAlive= false;
	m_xExperiance = 10;
}
Entity::Entity(float a_fXPos,float a_fYPos,float a_fXVel,float a_fYVel)
{
	Sprite();
	SetPos(Vector2(a_fXPos,a_fYPos));
	SetVel(Vector2(a_fXVel,a_fYVel));
	m_bisAlive= false;
}
Entity::Entity(float a_fXPos,float a_fYPos)
{
	Sprite();
	SetPos(Vector2(a_fXPos,a_fYPos));
	m_bisAlive= false;
}
Entity::Entity(Vector2 a_vPos,Vector2 a_vVel)
{
	Sprite();
	SetPos(a_vPos);
	SetVel(a_vVel);
	m_bisAlive= false;

}
Entity::Entity(Vector2 a_vPos)
{

	Sprite();
	SetPos(a_vPos);
	m_bisAlive= false;

}

Entity::~Entity(void)
{


}


void Entity::Update()
{

	if(m_bisAlive)
	{
		Sprite::Draw();
		Sprite::Update();
		GetCollider().SetCenter(GetPos());
	}
}




//figure this out maybe ApplyDamage could return XP?
xp Entity::Kill()
{
	m_bisAlive = false;
	Sprite::SetPos(Vector2(-100,-100));
	Sprite::SetVel(Vector2(0,0));
	return m_xExperiance;
}
void Entity::Respawn()
{
	m_bisAlive = true;
}
void Entity::Respawn(Vector2 a_vPos,Vector2 a_vVel)
{
	m_bisAlive = true;
	SetPos(a_vPos);
	SetVel(a_vVel);

}
void Entity::ApplyDamage(float a_fDam)
{
	m_fHealth -= a_fDam;
	if(m_fHealth > 0)
	{
		Kill();
	}
}





