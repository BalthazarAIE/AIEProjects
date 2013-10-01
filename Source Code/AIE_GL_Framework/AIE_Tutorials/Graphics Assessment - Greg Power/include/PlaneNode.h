#ifndef _PLANENODE_H_
#define _PLANENODE_H_

#include "MeshNode.h"

class PlaneNode : public MeshNode
{
public:
					PlaneNode( float a_fWidth, float a_fHeight, int a_iVertsWidth, int a_iVertsLength, AIE::vec4 a_translation, SceneNode *a_pParent = nullptr  );
					~PlaneNode();
	void			BuildVertsIndices();
	void			Update( float a_fDeltaTime );
	void			Draw();
protected:
	float			m_fWidth, m_fHeight;
	int				m_iVertsWidth;
	int				m_iVertsLength;
};

#endif