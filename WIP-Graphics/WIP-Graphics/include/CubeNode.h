#ifndef _CUBENODE_H_
#define _CUBENODE_H_

#include "MeshNode.h"

class CubeNode : public MeshNode
{
public:
					CubeNode( float a_fSize, AIE::vec4 a_translation, SceneNode *a_pParent = nullptr );
					~CubeNode();
	void			Update( float a_fDeltaTime );
	virtual void	Draw();
};

#endif