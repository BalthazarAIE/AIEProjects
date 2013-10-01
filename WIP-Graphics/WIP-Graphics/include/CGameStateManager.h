//----------------------------------------------------------------------//
//																		//	
//	FILENAME:		CGameStateManager.h									//
//	AUTHOR:			Greg Power											//
//	DESCRIPTION:	Draws and Updates all the gamestates.				//
//	DATE:			27/08/2012											//
//																		//
// CGameStateManager *gm = new CGameStateManager(pGame);				//
// SomeGameState *ptrToGameStateClass = new SomeGameState(pGame);		//
// gm->RegisterGameState(GAME_STATE_ENUM, ptrToGameStateClass);			//
//																		//
// gm->PushState(GAME_STATE_ENUM);										//
// gm->PopState();														//
//																		//
// gm->UpdateGameStates();												//
//																		//
// gm->DrawGameState();													//
//																		//
// delete gm;															//
//																		//
//----------------------------------------------------------------------//

#ifndef _CGAMESTATEMANAGER_H_
#define _CGAMESTATEMANAGER_H_

#include "IBaseGameState.h"
#include <vector>

class CGameStateManager
{
public:
				CGameStateManager(CApplication *pApp, unsigned int maxGameStates);
				~CGameStateManager();

	void		RegisterGameState(EGameState state, IBaseGameState* gameState);
	void		PushState(EGameState state);
	void		PopState();
	void		UpdateGameStates(float a_fDeltaTime);
	void		DrawGameStates();

	int			GetCurrentState();

private:

	enum EStateCommands
	{
		PUSH,
		POP
	};

	struct SStateCommands
	{
		EStateCommands cmd;
		EGameState state;
	};

	std::vector<SStateCommands>		m_oCommandList;

	std::vector<IBaseGameState*>	m_oRegisteredStates;
	std::vector<IBaseGameState*>	m_oStateStack;

};

#endif