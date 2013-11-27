#include "CircleCollider.h"


CircleCollider::CircleCollider(void)
{
	m_fRadius = 1;
	m_vCenter  = Vector2();
}

CircleCollider::CircleCollider(float a_fRadius,Vector2& a_vCenter)
{
	m_fRadius = a_fRadius;
	m_vCenter  = a_vCenter;
}


CircleCollider::~CircleCollider(void)
{
}


bool CircleCollider::CollisionCheck(CircleCollider& a_oOtherCircle)
{
	float lhs = (m_fRadius * m_fRadius) + (a_oOtherCircle.GetRadius() * a_oOtherCircle.GetRadius());
	float rhsX = (a_oOtherCircle.GetCenter().GetX() - m_vCenter.GetX());
	float rhsY = (a_oOtherCircle.GetCenter().GetY() - m_vCenter.GetY());

	if(lhs > ((rhsX*rhsX)+(rhsY*rhsY)))
		return true;
	return false;
}
bool CircleCollider::CollisionCheck(Vector2& a_vPoint)
{
	float lhs = (m_fRadius * m_fRadius);
	float rhsX = (a_vPoint.GetX() - m_vCenter.GetX());
	float rhsY = (a_vPoint.GetY() - m_vCenter.GetY());

	if(lhs > ((rhsX*rhsX)+(rhsY*rhsY)))
		return true;
	return false;

}	
bool CircleCollider::CollisionCheck(Vector2& a_vPointOne,Vector2& a_vPointTwo)
{	
	Vector2 NormOne(a_vPointOne.GetX() - m_vCenter.GetX(),a_vPointOne.GetY() - m_vCenter.GetY());
	Vector2 NormTwo(a_vPointTwo.GetX() - m_vCenter.GetX(),a_vPointTwo.GetY() - m_vCenter.GetY());

	float lengthX = NormTwo.GetX() - NormOne.GetX();
	float lengthY = NormTwo.GetY() - NormOne.GetY();
	float lengthCenterX = NormOne.GetX();
	float lengthCenterY = NormOne.GetY();


	float dotProduct  = Dot()

}
bool CircleCollider::CollisionCheck(Line2& a_lLine)
{

	return CollisionCheck(a_lLine.PointOne,a_lLine.PointTwo);
}