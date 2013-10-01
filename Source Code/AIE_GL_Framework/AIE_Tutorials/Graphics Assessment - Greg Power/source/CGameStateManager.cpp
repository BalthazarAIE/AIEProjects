#include "CGameStateManager.h"

CGameStateManager::CGameStateManager(CApplication *pApp, unsigned int maxGameStates)
{
	m_oRegisteredStates = std::vector<IBaseGameState*>( maxGameStates, NULL );
}

CGameStateManager::~CGameStateManager()
{
	for(int i = m_oStateStack.size() - 1; i >= 0; --i)
	{
		m_oStateStack[i]->Unload();
	}
	m_oStateStack.clear();

	for(int i = m_oRegisteredStates.size() - 1; i >= 0; --i)
	{
		if( m_oRegisteredStates[i] == nullptr )
			continue;

		delete m_oRegisteredStates[i];
		m_oRegisteredStates[i] = nullptr;
	}
}

void CGameStateManager::RegisterGameState(EGameState state, IBaseGameState* gameState)
{
	m_oRegisteredStates[ state ] = gameState;
}

int CGameStateManager::GetCurrentState()
{
	int currState = m_oStateStack[m_oStateStack.size() - 1]->GetStateID();
	return currState;
}

void CGameStateManager::PushState(EGameState state)
{
	if( state == NUM_GAME_STATES )
		state = LAB_01;
	SStateCommands command;
	command.cmd = PUSH;
	command.state = state;

	m_oCommandList.push_back(command);
}

void CGameStateManager::PopState()
{
	SStateCommands command;
	command.cmd = POP;
	command.state = NONE;

	m_oCommandList.push_back(command);
}

void CGameStateManager::UpdateGameStates(float a_fDeltaTime)
{
	for(int i = m_oStateStack.size() - 1; i >= 0; --i)
	{
		m_oStateStack[i]->Update(a_fDeltaTime);
	}

	for(unsigned int i = 0; i < m_oCommandList.size(); ++i)
	{
		if( m_oCommandList[i].cmd == PUSH )
		{
			IBaseGameState* state = m_oRegisteredStates[ m_oCommandList[i].state ];
			if( state != NULL )
			{
				state->Load();
				m_oStateStack.push_back( state );
			}
		}
		else if( m_oCommandList[i].cmd == POP && m_oStateStack.size() > 0)
		{
			m_oStateStack.back()->Unload();
			m_oStateStack.pop_back();
		}
	}

	m_oCommandList.clear();
}

void CGameStateManager::DrawGameStates()
{
	for(unsigned int i = 0; i < m_oStateStack.size(); ++i)
	{
		m_oStateStack[i]->Draw();
	}
}