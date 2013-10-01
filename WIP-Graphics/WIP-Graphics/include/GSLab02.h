#ifndef _GSLAB02_H_
#define _GSLAB02_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "Skybox.h"

class GSLab02 : public IBaseGameState
{
public:
				GSLab02(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab02();
	void		Load();
	void		Unload();
	void		Update(float a_fDeltaTime);
	void		Draw();

	int			GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*		m_poCamera;
	EGameState	m_eStateID;
	
	Quaternion	m_qPlaneRot;
	float		m_fTimer;

	Skybox*		m_poRoom;
	PlaneNode*	m_poTitle;
	PlaneNode*	m_poPainting01;
	PlaneNode*	m_poPainting02;
	PlaneNode*	m_poPainting03;
};

#endif