#include "CApplication.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>

#include "Utilities.h"
#include "CGameStateManager.h"
#include "CInputHandler.h"
#include "CRenderManager.h"
#include "GSLab01.h"
#include "GSLab02.h"
#include "GSLab03.h"
#include "GSLab04.h"
#include "GSLab05.h"
#include "GSLab07.h"
#include "GSLab08.h"
#include "GSLab09.h"

#include <cmath>

CApplication::CApplication(int a_iWindowWidth, int a_iWindowHeight, bool a_bFullscreen)
{
	m_iWindowWidth			= a_iWindowWidth;
	m_iWindowHeight			= a_iWindowHeight;
	m_bFullscreen			= a_bFullscreen;
	m_bGameOver				= false;

	m_poGameStateManager	= NULL;
	m_poInputHandler		= NULL;
	m_poRenderManager		= NULL;
}

CApplication::~CApplication()
{
}

void CApplication::Run()
{
	InitOpenGL();
	LoadAssets();

	do
	{
		float fDeltaTime = AIE::GetDeltaTime();
		if( fDeltaTime > 1/60.f )
			fDeltaTime = 1/60.f;

		glClear(GL_COLOR_BUFFER_BIT);
		m_poInputHandler->ProcessEvents();
		Update(fDeltaTime);
		
		Draw();

		glfwSwapBuffers();
	} while ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_RELEASE &&
		glfwGetWindowParam( GLFW_OPENED ) != 0 );

	FreeAssets();

	CloseOpenGL();
}

void CApplication::InitOpenGL()
{
	// start GLFW and open a window
	glfwInit();

	// get the desktop mode
	GLFWvidmode oMode;
	glfwGetDesktopMode(&oMode);

	// open a window
	glfwOpenWindow(	m_iWindowWidth, m_iWindowHeight,	// resolution
		oMode.RedBits,oMode.GreenBits,oMode.BlueBits,0,	// bits per colour channel (RGBA)
		24,												// depth bits
		8,												// stencil bits
		m_bFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW); // set windowed or fullscreen mode
	glfwSetWindowTitle("Greg Power - Graphics Assignment");

	// start GLEW
	if (glewInit() != GLEW_OK) glfwTerminate();

	// set clear colour
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// start our timer
	AIE::ResetTimer();
}

void CApplication::CloseOpenGL()
{
	glfwTerminate();
}

AIE::vec2 CApplication::GetWindowSize()
{
	AIE::vec2 windowSize;
	windowSize.x = static_cast <float> (m_iWindowWidth);
	windowSize.y = static_cast <float> (m_iWindowHeight);

	return windowSize;
}

void CApplication::LoadAssets()
{
	m_poInputHandler		= new CInputHandler();
	m_poGameStateManager	= new CGameStateManager( this, NUM_GAME_STATES );
	m_poRenderManager		= new CRenderManager();

	m_poGameStateManager->RegisterGameState(LAB_01, new GSLab01(LAB_01, this) );
	m_poGameStateManager->RegisterGameState(LAB_02, new GSLab02(LAB_02, this) );
	m_poGameStateManager->RegisterGameState(LAB_03, new GSLab03(LAB_03, this) );
	m_poGameStateManager->RegisterGameState(LAB_04, new GSLab04(LAB_04, this) );
	m_poGameStateManager->RegisterGameState(LAB_05, new GSLab05(LAB_05, this) );
	m_poGameStateManager->RegisterGameState(LAB_07, new GSLab07(LAB_07, this) );
	m_poGameStateManager->RegisterGameState(LAB_08, new GSLab08(LAB_08, this) );
	m_poGameStateManager->RegisterGameState(LAB_09, new GSLab09(LAB_09, this) );

	m_poGameStateManager->PushState( LAB_01 );
}

void CApplication::FreeAssets()
{
	if( m_poGameStateManager != NULL )
	{
		delete m_poGameStateManager;
		m_poGameStateManager = NULL;
	}

	if( m_poInputHandler != NULL )
	{
		delete m_poInputHandler;
		m_poInputHandler = NULL;
	}

	if( m_poRenderManager != NULL )
	{
		delete m_poRenderManager;
		m_poRenderManager = NULL;
	}
}

void CApplication::Update(float a_fDeltaTime)
{
	if( m_poInputHandler->IsSpaceDown() )
	{
		int currState = m_poGameStateManager->GetCurrentState();
		m_poGameStateManager->PopState();
		m_poGameStateManager->PushState( static_cast<EGameState>(currState+1) );
	}

	m_poGameStateManager->UpdateGameStates( a_fDeltaTime );
	m_poInputHandler->Update();
	m_poRenderManager->Update( a_fDeltaTime );
}

void CApplication::Draw()
{
	m_poGameStateManager->DrawGameStates();
}