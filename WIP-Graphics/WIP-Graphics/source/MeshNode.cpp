#include "MeshNode.h"

MeshNode::MeshNode( AIE::vec4 a_translation, SceneNode *a_pParent )
	: SceneNode( a_translation, a_pParent )
{
	//m_poRenderManager = nullptr;
	m_iTextureID = 0;
	m_iSecondaryTextureID = 0;
	m_iDisplacementTexID = 0;

	m_vColour = AIE::vec4( 0.f, 0.f, 0.f, 0.f );
}

MeshNode::~MeshNode()
{
	if( m_iTextureID != 0 )
		glDeleteTextures(	1, &m_iTextureID);
	if( m_iSecondaryTextureID != 0 ) 
		glDeleteTextures(	1, &m_iSecondaryTextureID);
	if( m_iDisplacementTexID != 0 ) 
		glDeleteTextures(	1, &m_iDisplacementTexID);

	glDeleteVertexArrays(	1, &m_iVAO);
	glDeleteBuffers(		1, &m_iVBO);
	glDeleteBuffers(		1, &m_iIBO);
	glDeleteShader(			m_iShaderID);
}

void MeshNode::CreateBuffers()
{
	glGenBuffers(		1, &m_iVBO );
	glGenBuffers(		1, &m_iIBO );
	glGenVertexArrays(	1, &m_iVAO );
	
	glBindVertexArray( m_iVAO );
	glBindBuffer( GL_ARRAY_BUFFER,			m_iVBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,	m_iIBO );

	glBufferData( GL_ARRAY_BUFFER,			m_iNumVerts		* sizeof(AIE::Vertex),	&m_aoVertices[0],	GL_STATIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,	m_iNumIndices	* sizeof(unsigned int),	&m_auiIndex[0],		GL_STATIC_DRAW );

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), ((char*)0) + 16);

	glBindVertexArray(0);
}

void MeshNode::UpdateBuffers()
{
	glBindVertexArray( m_iVAO );
	glBindBuffer( GL_ARRAY_BUFFER,			m_iVBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,	m_iIBO );

	glBufferData( GL_ARRAY_BUFFER,			m_iNumVerts		* sizeof(AIE::Vertex),	&m_aoVertices[0],	GL_STATIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,	m_iNumIndices	* sizeof(unsigned int),	&m_auiIndex[0],		GL_STATIC_DRAW );

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), ((char*)0) + 16);

	glBindVertexArray(0);
}

void MeshNode::TranslateNode( AIE::vec4 a_vTrans )
{
	SceneNode::TranslateNode( a_vTrans );

	auto iter = m_aoVertices.begin();
	while( iter != m_aoVertices.end() )
	{
		iter->position += a_vTrans;
		++iter;
	}
}

void MeshNode::RotateNode( Quaternion &a_qRot )
{
	SceneNode::RotateNode( a_qRot );

	auto vertIter = m_aoVertices.begin();
	while( vertIter != m_aoVertices.end() )
	{
		vertIter->position = a_qRot * vertIter->position;
		++vertIter;
	}
}

void MeshNode::Update( float a_fDeltaTime )
{
	SceneNode::Update( a_fDeltaTime );
}

void MeshNode::Draw()
{
	//a_modelMatrix = GetWorldTransform();//m_localTransform * m_qRotation.ToMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_iTextureID );
	if( m_iSecondaryTextureID != 0 )
	{
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, m_iSecondaryTextureID );
	}
	if( m_iDisplacementTexID != 0 )
	{
		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_2D, m_iDisplacementTexID );
	}
	glBindVertexArray( m_iVAO );
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawElements( GL_TRIANGLE_STRIP, m_iNumIndices, GL_UNSIGNED_INT, 0 );
}
