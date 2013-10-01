#ifndef _GSLAB03_H_
#define _GSLAB03_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "IcosphereNode.h"
#include "Skybox.h"
#include "ParticleManager.h"

class GSLab03 : public IBaseGameState
{
public:
						GSLab03(EGameState a_eStateID, CApplication* a_pApp);
						~GSLab03();
	void				Load();
	void				Unload();
	void				Update(float a_fDeltaTime);
	void				Draw();

	int					GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*				m_poCamera;
	EGameState			m_eStateID;

	ParticleManager*	m_poParticleManager;
	IcosphereNode*		m_poSphere;
	Skybox*				m_poSkyBox;
	PlaneNode*			m_poTitle;
	
	Quaternion			m_qPlaneRot;
	float				m_fTimer;
};

#endif