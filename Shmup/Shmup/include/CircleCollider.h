#ifndef _CIRCLE_COLLIDER_H_
#define _CIRCLE_COLLIDER_H_
#include "Vector2.h"
#include "Line2.h"

class CircleCollider
{
public:
	CircleCollider(void);
	CircleCollider(float a_fRadius,Vector2& a_vCenter);

	~CircleCollider(void);
	inline float& GetRadius(){return m_fRadius;}
	inline void SetRadius(float a_fRadius){m_fRadius = a_fRadius;}
	inline Vector2& GetCenter(){return m_vCenter;}
	inline void SetCenter(Vector2 &a_vCenter){m_vCenter = a_vCenter;}

	bool CollisionCheck(CircleCollider& a_oOtherCircle);
	bool CollisionCheck(Line2& a_lLine);
	bool CollisionCheck(Vector2& a_vPoint);
	bool CollisionCheck(Vector2& a_vPointOne,Vector2& a_vPointTwo);

private:
	float m_fRadius;
	Vector2 m_vCenter;
	
};
#endif //_CIRCLE_COLLIDER_H_
