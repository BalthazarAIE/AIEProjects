#include "QuadMesh.h"

QuadMesh::QuadMesh()
{	
	m_uiTextureID = 0;
	m_iSecondaryTextureID = 0;
	m_iDisplacementTexID = 0;
}

QuadMesh::~QuadMesh()
{
}

void QuadMesh::Init()
{
	//Create mesh
	aoVertices[0].position = AIE::vec4( -1.f, -1.f, 0.f, 1.f );
	aoVertices[0].uv = AIE::vec2( 0.f, 0.f );
	aoVertices[1].position = AIE::vec4(1.f, -1.f, 0.f, 1.f);
	aoVertices[1].uv = AIE::vec2(1.f, 0.f);
	aoVertices[2].position = AIE::vec4(1.f, 1.f, 0.f, 1.f);
	aoVertices[2].uv = AIE::vec2(1.f, 1.f);
	aoVertices[3].position = AIE::vec4(-1.f, 1.f, 0.f, 1.f);
	aoVertices[3].uv = AIE::vec2(0.f, 1.f);

	unsigned int auiIndex[6] = {
		0,1,3,
		1,2,3
	};

	//Create and bind buffers to a vertex array object
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiIBO);
	glGenVertexArrays(1, &m_uiVAO);

	glBindVertexArray(m_uiVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	glBufferData(GL_ARRAY_BUFFER,			4 * sizeof(AIE::Vertex),	aoVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,	6 * sizeof(unsigned int),	auiIndex,	GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(AIE::Vertex), ((char*)0) + 16);

	//Unbind vertex array
	glBindVertexArray(0);
}

void QuadMesh::Update()
{
}

void QuadMesh::Draw()
{
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_uiTextureID );
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
	glBindVertexArray( m_uiVAO );
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}
