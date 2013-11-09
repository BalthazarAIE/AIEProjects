#ifndef _CIRCLE_COLLIDER_H_
#define _CIRCLE_COLLIDER_H_
#include "Vector2.h"

class CircleCollider
{
public:
	CircleCollider(void);
	~CircleCollider(void);
	inline float& GetRadius(){return m_fRadius;}
	inline void SetRadius(float a_fRadius){m_fRadius = a_fRadius;}
	inline Vector2& GetRadius(){return m_vCenter;}
	inline void SetCenter(Vector2 &a_vCenter){m_vCenter = a_vCenter;}

	bool CollisionCheck(CircleCollider& a_oOtherCircle);

private:
	float m_fRadius;
	Vector2 m_vCenter;

};
#endif //_CIRCLE_COLLIDER_H_
