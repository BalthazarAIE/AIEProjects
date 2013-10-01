//----------------------------------------------------------------------//
//																		//	
//	FILENAME:		IBaseGameState.h									//
//	AUTHOR:			Greg Power (via Aaron Cox)							//
//	DESCRIPTION:	Abstract base game state class.						//
//	DATE:			27/08/2012											//
//																		//
//----------------------------------------------------------------------//

#ifndef _IBASEGAMESTATE_H_
#define _IBASEGAMESTATE_H_

enum EGameState
{
	LAB_01 = 0,
	LAB_02,
	LAB_03,
	LAB_04,
	LAB_05,
	LAB_07,
	LAB_08,
	LAB_09,

	//Do not remove these last two enum states,
	//they are used within the game state manager
	NUM_GAME_STATES,
	NONE
};

class CApplication;

class IBaseGameState
{
public:
	IBaseGameState(CApplication *pApp)
	{
		m_pApp = pApp;
	}

	virtual void Load()						= 0;
	virtual void Unload()					= 0;
	virtual void Update(float a_fDeltaTime)	= 0;
	virtual void Draw()						= 0;
	virtual int	GetStateID()				= 0;

	CApplication* GetApplication() { return m_pApp; }

protected:
	CApplication *m_pApp;
};

#endif