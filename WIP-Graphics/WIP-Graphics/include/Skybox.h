#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "MeshNode.h"

class Skybox : public MeshNode
{
public:
					Skybox( float a_fSize, AIE::vec4 a_translation = AIE::vec4(0.f,0.f,0.f,1.f), SceneNode *a_pParent = nullptr );
					~Skybox();
	void			Update( float a_fDeltaTime );
	void			Draw();
};

#endif