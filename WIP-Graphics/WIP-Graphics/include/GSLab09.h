#ifndef _GSLAB09_H_
#define _GSLAB09_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "PlaneNode.h"
#include "FBXLoader.h"

class GSLab09 : public IBaseGameState
{
public:
				GSLab09(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab09();
	void		Load();
	void		Unload();
	void		Update(float a_fDeltaTime);
	void		Draw();
	void		InitFBXSceneResources(FBXScene* a_pScene);
	void		DestroyFBXSceneResources(FBXScene* a_pScene);

	int			GetStateID() { return static_cast<int>( m_eStateID ); }
private:
	Camera*		m_poCamera;
	EGameState	m_eStateID;
	PlaneNode*	m_poTitle;
	FBXScene	m_oScene;
		
	float		m_fTimer;
};

#endif