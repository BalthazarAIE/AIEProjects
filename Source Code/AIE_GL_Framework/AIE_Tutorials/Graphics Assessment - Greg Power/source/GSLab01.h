#ifndef _GSLAB01_H_
#define _GSLAB01_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "Skybox.h"

class GSLab01 : public IBaseGameState
{
public:
				GSLab01(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab01();
	void		Load();
	void		Unload();
	void		Update(float a_fDeltaTime);
	void		Draw();

	int			GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*		m_poCamera;
	EGameState	m_eStateID;
	PlaneNode*	m_poTitlePlane;
	PlaneNode*	m_poWaterPlane;
	PlaneNode*	m_poCobbleStonePlane;
	PlaneNode*	m_poWallPlane01;
	PlaneNode*	m_poWallPlane02;
	PlaneNode*	m_poWallPlane03;
	Skybox*		m_poSkybox;
	
	Quaternion	m_qPlaneRot;
	float		m_fTimer;

};

#endif