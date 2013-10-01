#include "Camera.h"

Camera::Camera()
{
	m_vCameraPos = AIE::vec4( 0.f, 0.f, 0.f, 1.f );
	m_cameraMatrix.SetFrame( m_vCameraPos, vec4(0,0,1,0), vec4(0,1,0,0) );
}

Camera::Camera( const Camera& other )
{
	m_vCameraPos = other.m_vCameraPos;
	m_qCameraRot = other.m_qCameraRot;
}

Camera::Camera( const AIE::vec4& a_rvPosition, const Quaternion& a_rqRotation )
{
	m_vCameraPos = a_rvPosition;
	m_qCameraRot = a_rqRotation;
}

Camera::Camera( const AIE::vec4& a_rvPosition, const AIE::vec4& a_rvFacing, const AIE::vec4& a_rvUp )
{
	m_vCameraPos = a_rvPosition;
	m_cameraMatrix.SetFrame( m_vCameraPos, a_rvFacing, a_rvUp );
}

Camera::~Camera()
{
}

//void Camera::Initialize()
//{
//	m_cameraMatrix.SetFrame( m_vCameraPos, vec4(-1,0,0,0), vec4(0,1,0,0) );
//}

mat4 Camera::GetViewMatrix()
{
	//AIE::mat4 returnMat = m_qCameraRot.ToMatrix();
	//returnMat.row3 = m_vCameraPos;
	//return returnMat.ToViewMatrix();

	return m_cameraMatrix;
}

void Camera::Update( float a_fDeltaTime )
{
	m_fTimer += a_fDeltaTime;
	FreeMovement( a_fDeltaTime, 10 );

	//m_qCameraRot.w = sin(  m_fTimer );
	//m_cameraMatrix = m_qCameraRot.ToMatrix();
	//m_cameraMatrix.row3 = m_cameraPos;

	//m_pSceneNode->SetLocalTransform( m_pSceneNode->GetWorldTransform() );

	//m_cameraMatrix = m_pSceneNode->GetLocalTransform() * m_pSceneNode->GetWorldTransform();
	
	//m_pSceneNode->GetLocalTransform().row3	= m_cameraPos;
	//m_pSceneNode->GetLocalTransform()			= m_pSceneNode->GetLocalTransform() * m_pSceneNode->GetWorldTransform();
	//m_cameraMatrix.row3						= m_cameraPos;
}

void Camera::FreeMovement( float a_fDeltaTime, float a_fSpeed )
{
	// update mouse wheel
	static int siPrevMouseWheel = 0;
	int iMouseWheel				= glfwGetMouseWheel();
	int iMouseWheelDelta		= iMouseWheel - siPrevMouseWheel;
	siPrevMouseWheel			= iMouseWheel;

	// Get the camera's forward, right, up, and location vectors
	AIE::vec4 vForward		= m_cameraMatrix.row2;
	AIE::vec4 vRight		= m_cameraMatrix.row0;
	AIE::vec4 vUp			= m_cameraMatrix.row1;
	AIE::vec4 vTranslation	= m_cameraMatrix.row3;

	// Translate camera
	float fSpeed = glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS ? a_fSpeed * 2 : a_fSpeed;	

	if (glfwGetKey('W') == GLFW_PRESS)
	{
		vTranslation += vForward * (a_fDeltaTime * fSpeed);
	}
	if (glfwGetKey('S') == GLFW_PRESS)
	{
		vTranslation -= vForward * (a_fDeltaTime * fSpeed);
	}
	if (glfwGetKey('D') == GLFW_PRESS)
	{
		vTranslation += vRight * (a_fDeltaTime * fSpeed);
	}
	if (glfwGetKey('A') == GLFW_PRESS)
	{
		vTranslation -= vRight * (a_fDeltaTime * fSpeed);
	}
	if (glfwGetKey('Q') == GLFW_PRESS)
	{
		vTranslation += vUp * (a_fDeltaTime * fSpeed);
	}
	if (glfwGetKey('E') == GLFW_PRESS)
	{
		vTranslation -= vUp * (a_fDeltaTime * fSpeed);
	}
	if (iMouseWheelDelta != 0)
	{
		vTranslation += vForward * (a_fDeltaTime * fSpeed * iMouseWheelDelta);
	}

	m_cameraMatrix.row3 = vTranslation;

	// check for camera rotation
	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		static int siPrevMouseX = 0;
		static int siPrevMouseY = 0;

		if (sbMouseButtonDown == false)
		{
			sbMouseButtonDown = true;
			glfwGetMousePos(&siPrevMouseX,&siPrevMouseY);
		}

		int iMouseX = 0, iMouseY = 0;
		glfwGetMousePos(&iMouseX,&iMouseY);

		int iDeltaX = iMouseX - siPrevMouseX;
		int iDeltaY = iMouseY - siPrevMouseY;

		siPrevMouseX = iMouseX;
		siPrevMouseY = iMouseY;

		AIE::mat4 mMat;
		
		// pitch
		if (iDeltaY != 0)
		{
			mMat.RotateAxis(-iDeltaY / 150.f, vRight);
			vForward = mMat * vForward;
			vUp = mMat * vUp;
			vRight = mMat * vRight;
		}

		// yaw
		if (iDeltaX != 0)
		{
			mMat.RotateAxis(-iDeltaX / 150.0f, AIE::vec4(0,1,0,0) );
			vForward = mMat * vForward;
			vUp = mMat * vUp;
			vRight = mMat * vRight;
		}

		m_cameraMatrix.row0 = vRight;
		m_cameraMatrix.row1 = vUp;
		m_cameraMatrix.row2 = vForward;
	}
	else
	{
		sbMouseButtonDown = false;
	}
}