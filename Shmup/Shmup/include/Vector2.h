#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

class Vector2
{
public:
	Vector2(void);
	Vector2(float a_fX,float a_fY);
	Vector2(Vector2 &a_rV);
	~Vector2(void);

	inline float& GetX(){return m_fX;}
inline float& GetY(){return m_fY;}

inline void SetX(float a_fX){m_fX = a_fX;}
inline void SetY(float a_fY){m_fY = a_fY;}

	Vector2 operator + (Vector2 &a_rV);
	Vector2 operator + (float a_fS);
	Vector2& operator += (Vector2 &a_rV);
	Vector2& operator += (float a_fS);

	Vector2 operator - (Vector2 &a_rV);
	Vector2 operator - (float a_fS);
	Vector2& operator -= (Vector2 &a_rV);
	Vector2& operator -= (float a_fS);


	Vector2 operator * (float a_fS);
	Vector2& operator *= (float a_fS);

	float Dot(Vector2 &a_rV);
	float Dot(float& a_fX,float& a_fY);
	float Magnatude();
	float SqMagnatude();

	Vector2 Norm();
	void Normalize();

	static Vector2& Zero();
	float SqrDis(Vector2 &a_rOther);
	

private:
	float m_fX;
	float m_fY;
};

#endif //_VECTOR2_H_

