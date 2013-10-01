#ifndef _TERRAINNODE_H_
#define _TERRAINNODE_H_

#include "MeshNode.h"

class TerrainNode : public MeshNode
{
public:
			TerrainNode( float a_fWidth, float a_fLength, float a_fHeightScale, int a_iVertsWidth, int a_iVertsLength, AIE::vec4 a_translation, SceneNode *a_pParent = nullptr );
			~TerrainNode();
	void	BuildVertsIndices();
	void	Update( float a_fDeltaTime );
	void	Draw();
private:
	float			m_fWidth, m_fLength, m_fHeightScale;
	int				m_iVertsWidth;
	int				m_iVertsLength;
};

#endif