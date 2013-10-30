#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	m_fX = 0;
	m_fY = 0;
}
Vector2::Vector2(float a_fX,float a_fY)
{
	m_fX = a_fX;
	m_fY = a_fY;
}
Vector2::Vector2(Vector2 &a_rV)
{
	m_fX = a_rV.m_fX;
	m_fY = a_rV.m_fY;
}
Vector2::~Vector2(void)
{
}

float& Vector2::GetX(){return m_fX;}
float& Vector2::GetY(){return m_fY;}

void Vector2::SetX(float a_fX){m_fX = a_fX;}
void Vector2::SetY(float a_fY){m_fY = a_fY;}


Vector2 Vector2::operator + (Vector2 &a_rV)
{
	Vector2 temp;
	temp.m_fX = m_fX + a_rV.m_fX;
	temp.m_fY = m_fY + a_rV.m_fY;
	return temp;

}
Vector2 Vector2::operator + (float a_fS)
{
	Vector2 temp;
	temp.m_fX = m_fX + a_fS;
	temp.m_fY = m_fY + a_fS;
	return temp;
}
Vector2& Vector2::operator += (Vector2 &a_rV)
{
	m_fX += a_rV.m_fX;
	m_fY += a_rV.m_fY;
	return *this;
}
Vector2& Vector2::operator += (float a_fS)
{
	m_fX += a_fS;
	m_fY += a_fS;
	return *this;
}

Vector2 Vector2::operator - (Vector2 &a_rV)
{
	Vector2 temp;
	temp.m_fX = m_fX - a_rV.m_fX;
	temp.m_fY = m_fY - a_rV.m_fY;
	return temp;

}
Vector2 Vector2::operator - (float a_fS)
{
	Vector2 temp;
	temp.m_fX = m_fX - a_fS;
	temp.m_fY = m_fY - a_fS;
	return temp;
}
Vector2& Vector2::operator -= (Vector2 &a_rV)
{
	m_fX -= a_rV.m_fX;
	m_fY -= a_rV.m_fY;
	return *this;
}
Vector2& Vector2::operator -= (float a_fS)
{
	m_fX -= a_fS;
	m_fY -= a_fS;
	return *this;
}

Vector2 Vector2::operator * (float a_fS)
{
	Vector2 temp;
	temp.m_fX = m_fX * a_fS;
	temp.m_fY = m_fY * a_fS;
	return temp;
}
Vector2& Vector2::operator *= (float a_fS)
{
	m_fX *= a_fS;
	m_fY *= a_fS;
	return *this;
}

float Vector2::Dot(Vector2 &a_rV)
{
	return (m_fX * a_rV.m_fX)+(m_fY * a_rV.m_fY);
}
float Vector2::Magnatude()
{
	return sqrt(SqMagnatude());
}
float Vector2::SqMagnatude()
{
	return ((m_fX*m_fX) +(m_fY*m_fY));
}
Vector2 Vector2::Norm()
{
	float mag = Magnatude();
	Vector2 temp;
	temp.m_fX = (m_fX/mag);
	temp.m_fY = (m_fY/mag);
	return temp;
}
void Vector2::Normalize()
{
	float mag = Magnatude();
	m_fX = (m_fX/mag);
	m_fY = (m_fY/mag);


}
float Vector2::SqrDis(Vector2 &a_rOther)
	{
		return  (a_rOther.GetX() - GetX()) * (a_rOther.GetX() - GetX()) 
			+ (a_rOther.GetY() - GetY()) * (a_rOther.GetY() - GetY());
	}
void Vector2::Zero()
{
	m_fX = m_fY =0;
}

