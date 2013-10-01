#ifndef _GSLAB04_H_
#define _GSLAB04_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "Skybox.h"

class GSLab04 : public IBaseGameState
{
public:
				GSLab04(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab04();
	void		Load();
	void		Unload();
	void		Update(float a_fDeltaTime);
	void		Draw();

	int			GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*		m_poCamera;
	EGameState	m_eStateID;

	PlaneNode*  m_poTitle;
	PlaneNode*	m_poTerrain;
	
	Quaternion	m_qPlaneRot;
	float		m_fTimer;
};

#endif