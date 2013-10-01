#include "CInputHandler.h"
#include <GL/glfw.h>

CInputHandler::CInputHandler()
{
	m_bIsLMBClicked	= false;
	m_bIsRMBDown_ThisFrame	= false;

	m_oMousePos.x = 0.0f;
	m_oMousePos.y = 0.0f;

	m_bLeftKeyDown		= false;
	m_bRightKeyDown		= false;
	m_bUpKeyDown		= false;
	m_bDownKeyDown		= false;
	m_bLeftShiftDown	= false;
	m_bAnyEvent			= false;

	m_bAnyKeyDown = false;

	m_bSpaceUp		= true;
	m_bSpaceDown	= false;

}

CInputHandler::~CInputHandler()
{
}

void CInputHandler::ProcessEvents()
{
	if( glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS )
	{
		m_bIsLMBClicked = true;
		m_bAnyEvent		= true;
	}
	else if( glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE )
		m_bIsLMBClicked = false;

	if( glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS && m_bSpaceUp == true )
	{
		m_bSpaceDown = true;
		m_bSpaceUp = false;
	}
	if( glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE )
		m_bSpaceUp = true;
}

bool CInputHandler::IsDirKeyDown()
{
	return(m_bLeftKeyDown || m_bRightKeyDown || m_bUpKeyDown || m_bDownKeyDown);
}

void CInputHandler::Update()
{
	m_bAnyKeyDown	= false;
	m_bAnyEvent		= false;
	m_bSpaceDown	= false;
	//Reset all event bools
	//m_bIsLMBClicked = false;
}