
#include "Entity.h"
#include "Vector2.h"



Entity::Entity(void)
{
	Sprite();
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

	}
}

void Entity::SetXp(xp exp)
{
	m_xExperiance = exp;
}
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
bool Entity::isAlive()
{
	return m_bisAlive;
}
void Entity::ApplyDamage(float a_fDam)
{
	m_fHealth -= a_fDam;
	if(m_fHealth > 0)
	{
		Kill();
	}
}
bool Entity::CollisionCheck(Entity *other)
{
	
	if ((GetRadius()+ other->GetRadius())*(GetRadius()+ other->GetRadius()) >=  GetPos().SqrDis(other->GetPos()))
		return true;
return false;

}
bool Entity::CollisionCheck(Vector2 &point1,Vector2 &point2)
{
	if(point1.GetX() == point2.GetX())
	{
		if(point1.GetX() >= 0)
		{
			if((GetPos().GetX()-(GetWidth()/2) )< 0)
			{
				return true;
			}
			

		}
		if(point1.GetX() == SCREEN_WIDTH)
		{
			if((GetPos().GetX()+(GetWidth()/2) )> SCREEN_WIDTH)
			{
				return true;
			}
		
		}
	}

	else if(point1.GetY() == point2.GetY())
	{
		if(point1.GetY() >= 0)
		{
			if((GetPos().GetY()-(GetHeight()/2) )< 0)
			{
				return true;
			}
			

		}
		if(point1.GetY() == SCREEN_HEIGHT)
		{
			if((GetPos().GetY()+(GetHeight()/2) )> SCREEN_HEIGHT)
			{
				return true;
			}
		
		}
	
	}
	return false;


}



