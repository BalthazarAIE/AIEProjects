#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <MathHelper.h>

using namespace AIE;

class Quaternion
{
public:
	float w, x, y, z;

	Quaternion() : w(1.f), x(0.f), y(0.f), z(0.f) {};
	Quaternion(float a_w, float a_x, float a_y, float a_z) : w(a_w), x(a_x), y(a_y), z(a_z) {}
	~Quaternion() {}

	float Dot( const Quaternion& q ) const
	{
		return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
	}

	float Magnitude()
	{
		return sqrt( w*w + x*x + y*y + z*z );
	}

	Quaternion& Normalize()
	{
		float fScale = x*x + y*y * z*z + w*w;
		float fRScale = 1.0f / sqrtf(fScale);
		return ((*this) *= fRScale);
	}

	//void Normalize()
	//{
	//	float magnitude = sqrt( w*w + x*x + y*y + z*z );
	//	w /= magnitude;
	//	x /= magnitude;
	//	y /= magnitude;
	//	z /= magnitude;
	//}

	Quaternion GetConjugate()
	{
		Quaternion quat;
		quat.w = w;
		quat.x = -x;
		quat.y = -y;
		quat.z = -z;

		return quat;
	}

	AIE::vec4 GramSchmidtOrthonormalise( AIE::vec4 &v4Position, AIE::vec4 &v4KnownDirection, AIE::vec4 &v4WorldIdentity )
	{
		AIE::vec4 v4ThirdProjection = AIE::vec4( 0.f, 0.f, 0.f, 0.f );
		v4WorldIdentity = v4WorldIdentity - ( v4KnownDirection * v4KnownDirection.Dot(v4WorldIdentity) );
		v4WorldIdentity.Normalise();

		v4ThirdProjection = v4WorldIdentity.Cross( v4KnownDirection );
		v4ThirdProjection.Normalise();

		return v4ThirdProjection;
	}

	Quaternion operator * (const Quaternion& q) const
	{
		return	Quaternion( w*q.w - x*q.x - y*q.y - z*q.z,
							w*q.x + x*q.w + y*q.z - z*q.y,
							w*q.y - x*q.z + y*q.w + z*q.x,
							w*q.z + x*q.y - y*q.x + z*q.w	);

				
	}

	Quaternion& operator *= (const Quaternion& q)
	{
		float a = w*q.w - x*q.x - y*q.y - z*q.z;
		float b = w*q.x + x*q.w + y*q.z - z*q.y;
		float c = w*q.y - x*q.z + y*q.w + z*q.x;
		float d = w*q.z + x*q.y - y*q.x + z*q.w;

		w = a;
		x = b;
		y = c;
		z = d;

		return *this;
	}

	vec4 operator * (const vec4 &rhs)
	{
		Quaternion quat1( 0.f, rhs.x, rhs.y, rhs.z );

		Quaternion quat2 = (*this) * quat1;
		Quaternion quatInv = this->GetConjugate();
		Quaternion quat3 = quat2 * quatInv;

		return vec4( quat3.x, quat3.y, quat3.z, 1.0f );
	}

	Quaternion& operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return (*this);
	}

	Quaternion operator*(float rhs)
	{
		return Quaternion(rhs*x, rhs*y, rhs*z, rhs*w);
	}

	void CreateRotation( float a_fRad, AIE::vec4 a_vAxis )
	{
		w = cosf( a_fRad/2 );
		x = a_vAxis.x * sinf(a_fRad/2);
		y = a_vAxis.y * sinf(a_fRad/2);
		z = a_vAxis.z * sinf(a_fRad/2);
	}

	vec4 RotateVector( const vec4& a_vector )
	{
		Quaternion quat1( 0.f, a_vector.x, a_vector.y, a_vector.z );

		Quaternion quat2 = (*this) * quat1;
		Quaternion quatInv = this->GetConjugate();
		Quaternion quat3 = quat2 * quatInv;

		return vec4( quat3.x, quat3.y, quat3.z, 1.0f );

		/*Quaternion quat(	w*vec.w - x*vec.x	- y*vec.y	- z*vec.z,
							w*vec.x + x*vec.w	+ y*vec.z	+ z*vec.y,
							w*vec.y - x*vec.z	- y*vec.w	- z*vec.x,
							w*vec.z	+ x*vec.y	+ y*vec.x	+ z*vec.w	);

		vec.x = quat.x;
		vec.y = quat.y;
		vec.z = quat.z;

		Quaternion conj = this->GetConjugate();
		
		quat = Quaternion(	vec.w*conj.w - vec.x*conj.x	- vec.y*conj.y	- vec.z*conj.z,
							vec.w*conj.x + vec.x*conj.w	+ vec.y*conj.z	+ vec.z*conj.y,
							vec.w*conj.y - vec.x*conj.z	- vec.y*conj.w	- vec.z*conj.x,
							vec.w*conj.z + vec.x*conj.y	+ vec.y*conj.x	+ vec.z*conj.w	);
		
		vec.x = quat.x;
		vec.y = quat.y;
		vec.z = quat.z;
		vec.w = 1.0f;
		
		return vec;*/
	}

	mat4 ToMatrix()
	{
		mat4 matrix;

		matrix.row0.x = 1.f - 2.f * y*y - 2.f * z*z;
		matrix.row0.y = 2.f * x * y - 2.f * z * w;
		matrix.row0.z = 2.f * x * z + 2.f * y * w;
		matrix.row0.w = 0.f;

		matrix.row1.x = 2.f * x * y + 2 * z * w;
		matrix.row1.y = 1.f - 2.f * x*x - 2.f * z*z;
		matrix.row1.z = 2.f * z * y - 2.f * x * w;
		matrix.row1.w = 0.f;

		matrix.row2.x = 2.f * x * z - 2.f * y * w;
		matrix.row2.y = 2.f * z * y + 2.f * x * w;
		matrix.row2.z = 1.f - 2.f * x*x - 2.f * y*y;
		matrix.row2.w = 0.f;

		matrix.row3.x = 0.f;
		matrix.row3.y = 0.f;
		matrix.row3.z = 0.f;
		matrix.row3.w = 1.f;

		return matrix;
	}

	Quaternion FromMatrix( const mat4& a_matrix )
	{
		Quaternion quat;

		quat.w = sqrt( 1.f + a_matrix._11 + a_matrix._22 + a_matrix._33) / 2.f;
		quat.x = (a_matrix._32 - a_matrix._23) / (4.f * w);
		quat.y = (a_matrix._13 - a_matrix._31) / (4.f * w);
		quat.z = (a_matrix._21 - a_matrix._12) / (4.f * w);

		return quat;
	}

private:
};

#endif