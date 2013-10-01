//----------------------------------------------------------------------//
//																		//
//	AUTHOR:			Greg Power (via Aaron Cox)							//
//	DESCRIPTION:	OOP window creation and management wrapper for SDL	//
//					and basic game loop.								//
//	DATE:			20/08/2012											//
//																		//
//----------------------------------------------------------------------//

#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include "Utilities.h"

class CGameStateManager;
class CInputHandler;
class CRenderManager;

class CApplication
{
public:
	CApplication(int a_iWindowWidth, int a_iWindowHeight, bool a_bFullscreen = false);
	~CApplication();

	//function returns when the game loop exits
	void Run();

	CGameStateManager*	GetGameStateManager()	{ return m_poGameStateManager;	}
	CInputHandler*		GetInputHandler()		{ return m_poInputHandler;		}
	CRenderManager*		GetRenderManager()		{ return m_poRenderManager;		}

	AIE::vec2			GetWindowSize();

protected:
	void				InitOpenGL();
	void				CloseOpenGL();
	void				LoadAssets();
	void				FreeAssets();
	void				Update(float a_fDeltaTime);
	void				Draw();

	int					m_iWindowWidth;
	int					m_iWindowHeight;
	bool				m_bFullscreen;
	bool				m_bGameOver;

private:
	CGameStateManager*	m_poGameStateManager;
	CInputHandler*		m_poInputHandler;
	CRenderManager*		m_poRenderManager;
};


#endif