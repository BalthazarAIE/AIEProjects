#ifndef _ICOSPHERENODE_H_
#define _ICOSPHERENODE_H_

#include "MeshNode.h"

class IcosphereNode : public MeshNode
{
public:
			IcosphereNode( float a_fSize, AIE::vec4 a_translation, SceneNode *a_pParent = nullptr );
			~IcosphereNode();
	void	Update(float a_fDeltaTime);
	void	Draw();
private:
};

#endif