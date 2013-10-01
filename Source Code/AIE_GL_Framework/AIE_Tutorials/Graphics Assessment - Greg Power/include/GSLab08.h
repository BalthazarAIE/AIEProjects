#ifndef _GSLAB08_H_
#define _GSLAB08_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "Skybox.h"
#include "TerrainNode.h"
#include "IcosphereNode.h"

class GSLab08 : public IBaseGameState
{
public:
					GSLab08(EGameState a_eStateID, CApplication* a_pApp);
					~GSLab08();
	void			Load();
	void			Unload();
	void			Update(float a_fDeltaTime);
	void			Draw();

	int				GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*			m_poCamera;
	EGameState		m_eStateID;

	TerrainNode*	m_poTerrain;
	Skybox*			m_poSkyBox;
	PlaneNode*		m_poTitle;
	IcosphereNode*	m_poIcosphere;
	
	Quaternion		m_qPlaneRot;
	float			m_fTimer;
};

#endif