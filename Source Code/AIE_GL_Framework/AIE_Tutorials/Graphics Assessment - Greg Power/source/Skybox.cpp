#include "Skybox.h"

Skybox::Skybox( float a_fSize, AIE::vec4 a_translation, SceneNode *a_pParent )
	: MeshNode( a_translation, a_pParent )
{
	float fHalfSize = a_fSize * 0.5f;
	m_iNumVerts		= 14;
	m_iNumIndices	= 36;

	for( unsigned int i = 0; i < m_iNumVerts; ++i )
	{
		AIE::Vertex vert;	
		m_aoVertices.push_back( vert );
	}
	
	m_aoVertices[0].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + fHalfSize, a_translation.z + fHalfSize, 1.f );
	m_aoVertices[0].uv		= AIE::vec2( 0.2501f, 0.7499f );
	m_aoVertices[1].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + fHalfSize, a_translation.z + fHalfSize, 1.f );
	m_aoVertices[1].uv		= AIE::vec2( 0.499f, 0.7499f );
	m_aoVertices[2].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + -fHalfSize, a_translation.z + fHalfSize, 1.f );
	m_aoVertices[2].uv		= AIE::vec2( 0.499f, 0.5001f );
	m_aoVertices[3].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + -fHalfSize, a_translation.z + fHalfSize, 1.f );
	m_aoVertices[3].uv		= AIE::vec2( 0.2501f, 0.5001f );
	m_aoVertices[4].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[4].uv		= AIE::vec2( 0.9999f, 0.7499f );
	m_aoVertices[5].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[5].uv		= AIE::vec2( 0.75f, 0.7499f );
	m_aoVertices[6].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + -fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[6].uv		= AIE::vec2( 0.75f, 0.5001f );
	m_aoVertices[7].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + -fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[7].uv		= AIE::vec2( 0.9999f, 0.5001f );
	m_aoVertices[8].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[8].uv		= AIE::vec2( 0.2501f, 0.9999f );
	m_aoVertices[9].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[9].uv		= AIE::vec2( 0.4999f, 0.9999f );
	m_aoVertices[10].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + -fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[10].uv		= AIE::vec2( 0.2501f, 0.2501f );
	m_aoVertices[11].position	= AIE::vec4( a_translation.x + fHalfSize, a_translation.y + -fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[11].uv		= AIE::vec2( 0.4999f, 0.2501f );
	m_aoVertices[12].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[12].uv		= AIE::vec2( 0.0001f, 0.7499f );
	m_aoVertices[13].position	= AIE::vec4( a_translation.x + -fHalfSize, a_translation.y + -fHalfSize, a_translation.z + -fHalfSize, 1.f );
	m_aoVertices[13].uv		= AIE::vec2( 0.0001f, 0.5001f );

	unsigned int indices[36] = {
		3,1,0,
		3,2,1,
		2,5,1,
		2,6,5,
		6,4,5,
		6,7,4,
		10,2,3,
		10,11,2,
		13,0,12,
		13,3,0,
		0,9,8,
		0,1,9

	};

	m_auiIndex.insert(m_auiIndex.begin(), indices, indices+36);

	CreateBuffers();
}

Skybox::~Skybox()
{
}

void Skybox::Update( float a_fDeltaTime )
{
}

void Skybox::Draw()
{
	MeshNode::Draw();
}
