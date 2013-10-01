#include "IcosphereNode.h"

IcosphereNode::IcosphereNode( float a_fSize, AIE::vec4 a_translation, SceneNode *a_pParent )
	: MeshNode( a_translation, a_pParent )
{
	m_iNumVerts		= 12;
	m_iNumIndices	= 60;

	for( unsigned int i = 0; i < m_iNumVerts; ++i )
	{
		AIE::Vertex vert;	
		m_aoVertices.push_back( vert );
	}

	float t = (1.0f * sqrt(5.0f)) / 2.0f;

	m_aoVertices[0].position	= AIE::vec4( -1*a_fSize,  t*a_fSize, 0, 1.f );
	m_aoVertices[1].position	= AIE::vec4(  1*a_fSize,  t*a_fSize, 0, 1.f );
	m_aoVertices[2].position	= AIE::vec4( -1*a_fSize, -t*a_fSize, 0, 1.f );
	m_aoVertices[3].position	= AIE::vec4(  1*a_fSize, -t*a_fSize, 0, 1.f );

	m_aoVertices[4].position	= AIE::vec4( 0, -1*a_fSize,  t*a_fSize, 1.f );
	m_aoVertices[5].position	= AIE::vec4( 0,  1*a_fSize,  t*a_fSize, 1.f );
	m_aoVertices[6].position	= AIE::vec4( 0, -1*a_fSize, -t*a_fSize, 1.f );
	m_aoVertices[7].position	= AIE::vec4( 0,  1*a_fSize, -t*a_fSize, 1.f );

	m_aoVertices[8].position	= AIE::vec4(  t*a_fSize, 0, -1*a_fSize, 1.f );
	m_aoVertices[9].position	= AIE::vec4(  t*a_fSize, 0,  1*a_fSize, 1.f );
	m_aoVertices[10].position	= AIE::vec4( -t*a_fSize, 0, -1*a_fSize, 1.f );
	m_aoVertices[11].position	= AIE::vec4( -t*a_fSize, 0,  1*a_fSize, 1.f );



	if( a_pParent != nullptr )
	{
		mat4 globalTrans = a_pParent->GetWorldTransform();
		for( unsigned int i = 0; i < m_iNumVerts; ++i )
		{
			m_aoVertices[i].position += a_translation;
			m_aoVertices[i].position = globalTrans * m_aoVertices[i].position;
		}
	}

	unsigned int indices[60] = {
		5,	11, 0,
		1,	5,	0,
		7,	1,	0,
		10,	7,	0,
		11,	10, 0,
		9,	5,	1,
		4,	11, 5,
		2, 10, 11,
		6,	7,	10,
		8,	1,	7,
		4,	9,	3,
		2,	4,	3,
		6,	2,	3,
		8,	6,	3,
		9,	8,	3,
		5,	9,	4,
		11,	4,	2,
		10,	2,	6,
		7,	6,	8,
		1,	8,	9
	};

	m_auiIndex.insert(m_auiIndex.begin(), indices, indices+60);

	CreateBuffers();
}

IcosphereNode::~IcosphereNode()
{
}

void IcosphereNode::Update(float a_fDeltaTime)
{
	MeshNode::Update( a_fDeltaTime );
}

void IcosphereNode::Draw()
{
	MeshNode::Draw();
}