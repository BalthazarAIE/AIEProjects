#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glew.h>
#include <GL/glfw.h>

#include "MathHelper.h"
#include "Quaternion.h"
#include "SceneNode.h"

using namespace AIE;

class Camera
{
public:
				Camera();
				Camera( const Camera& other );
				Camera( const AIE::vec4& a_rvPosition, const Quaternion& a_rqRotation );
				Camera( const AIE::vec4& a_rvPosition, const AIE::vec4& a_rvFacing, const AIE::vec4& a_rvUp );

				~Camera();
	//void		Initialize();
	void		Update( float a_fDeltaTime );
	void		FreeMovement( float a_fDeltaTime, float a_fSpeed );

	mat4		GetViewMatrix();

	vec4		GetCameraPosition()							{ return m_vCameraPos; }
	void		SetCameraPosition( vec4 a_cameraPos )		{ m_cameraMatrix.row3 = a_cameraPos; }

	Quaternion	GetCameraRotation()							{ return m_qCameraRot; }
	void		SetCameraRotation( Quaternion a_cameraRot )	{ m_qCameraRot = a_cameraRot; }

protected:
	vec4		m_vCameraPos;
	Quaternion	m_qCameraRot;

	mat4		m_cameraMatrix;

	float		m_fTimer;
};

#endif