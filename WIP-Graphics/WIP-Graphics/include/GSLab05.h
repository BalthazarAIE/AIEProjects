#ifndef _GSLAB05_H_
#define _GSLAB05_H_

#include "IBaseGameState.h"
#include "Camera.h"
#include "FBXLoader.h"
#include "PlaneNode.h"

class GSLab05 : public IBaseGameState
{
public:
				GSLab05(EGameState a_eStateID, CApplication* a_pApp);
				~GSLab05();
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
	
	Quaternion	m_qPlaneRot;
	float		m_fTimer;
};

#endif