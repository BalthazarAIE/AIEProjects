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

	float& GetX();
	float& GetY();

	void SetX(float a_fX);
	void SetY(float a_fY);


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
	float Magnatude();
	float SqMagnatude();

	Vector2 Norm();
	void Normalize();

	void Zero();
	float SqrDis(Vector2 &a_rOther);
	

private:
	float m_fX;
	float m_fY;
};

#endif //_VECTOR2_H_

