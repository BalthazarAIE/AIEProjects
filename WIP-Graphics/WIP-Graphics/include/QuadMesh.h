#ifndef _QUADMESH_H_
#define _QUADMESH_H_

#include "Utilities.h"

class QuadMesh
{
public:
					QuadMesh();
					~QuadMesh();

	void			Init();
	void			SetTexture( GLuint a_uiTextureID )			{ m_uiTextureID = a_uiTextureID; }
	void			SetSecondaryTexture( GLuint a_uiTextureID ) { m_iSecondaryTextureID = a_uiTextureID; }
	void			SetDisplacementTexture(GLuint a_uiTextureID){ m_iDisplacementTexID = a_uiTextureID; }
	void			Update();
	void			Draw();

private:
	GLuint			m_uiVAO, m_uiVBO, m_uiIBO;
	GLuint			m_uiTextureID;
	GLuint			m_iSecondaryTextureID;
	GLuint			m_iDisplacementTexID;
	AIE::Vertex		aoVertices[14];
};

#endif 