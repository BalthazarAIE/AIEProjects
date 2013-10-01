#ifndef _GSLAB07_H_
#define _GSLAB07_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "Skybox.h"
#include "TerrainNode.h"
#include "ParticleManager.h"

class GSLab07 : public IBaseGameState
{
public:
				GSLab07(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab07();
	void		Load();
	void		Unload();
	void		Update(float a_fDeltaTime);
	void		Draw();

	int			GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*				m_poCamera;
	EGameState			m_eStateID;

	Skybox*				m_poSkybox;
	TerrainNode*		m_poTerrain;
	PlaneNode*			m_poTitle;
	PlaneNode*			m_poGlass;
	ParticleManager*	m_pParticleManager;
	
	Quaternion			m_qPlaneRot;
	float				m_fTimer;
};

#endif