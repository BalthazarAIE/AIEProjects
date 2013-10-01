//----------------------------------------------------------------------//
//																		//	
//	FILENAME:		CInputHandler.h										//
//	AUTHOR:			Greg Power											//
//	DESCRIPTION:	Input handling class. Receives a list of events		//
//					from CApplication, and process them.				//
//	DATE:			29/08/2012											//
//																		//
//----------------------------------------------------------------------//

#ifndef _CINPUTHANDLER_H_
#define _CINPUTHANDLER_H_

#include "Utilities.h"

class CInputHandler
{
public:
				CInputHandler();
				~CInputHandler();
	void		ProcessEvents();
				
	bool		IsLMBClicked()		{ return m_bIsLMBClicked;	}
	AIE::vec2	GetMousePosition()	{ return m_oMousePos;		}

	bool		IsDirKeyDown();
	bool		IsAnyKeyDown()		{ return m_bAnyKeyDown;		}
	bool		IsAnyEvent()		{ return m_bAnyEvent;		}
	bool		IsLeftKeyDown()		{ return m_bLeftKeyDown;	}
	bool		IsRightKeyDown()	{ return m_bRightKeyDown;	}
	bool		IsUpKeyDown()		{ return m_bUpKeyDown;		}
	bool		IsDownKeyDown()		{ return m_bDownKeyDown;	}
	bool		IsLeftShiftDown()	{ return m_bLeftShiftDown;	}
	bool		IsSpaceDown()		{ return m_bSpaceDown;		}

	void		Update();

private:
	bool		m_bIsLMBClicked;
	bool		m_bIsRMBDown_ThisFrame;
	AIE::vec2	m_oMousePos;

	bool		m_bLeftKeyDown;
	bool		m_bRightKeyDown;
	bool		m_bUpKeyDown;
	bool		m_bDownKeyDown;
	bool		m_bLeftShiftDown;
	bool		m_bAnyKeyDown;
	bool		m_bAnyEvent;
	bool		m_bSpaceDown;
	bool		m_bSpaceUp;
	
};

#endif