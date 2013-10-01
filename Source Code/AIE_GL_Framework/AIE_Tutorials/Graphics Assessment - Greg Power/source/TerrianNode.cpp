#include "TerrainNode.h"
#include "PerlinNoise2D.h"

TerrainNode::TerrainNode( float a_fWidth, float a_fLength, float a_fHeightScale, int a_iVertsWidth, int a_iVertsLength, AIE::vec4 a_translation, SceneNode *a_pParent ) 
	: MeshNode( a_translation, a_pParent )
{
	m_fWidth		= a_fWidth;
	m_fLength		= a_fLength;
	m_fHeightScale	= a_fHeightScale;

	m_iVertsWidth	= a_iVertsWidth;
	m_iVertsLength	= a_iVertsLength;

	if( m_iVertsWidth < 2 )
		m_iVertsWidth = 2;
	if( m_iVertsLength < 2 )
		m_iVertsLength = 2;

	BuildVertsIndices();
}

TerrainNode::~TerrainNode()
{
}

void TerrainNode::BuildVertsIndices()
{
	float fHalfWidth	= m_fWidth/2;
	float fHalfLength	=	m_fLength/2;
	AIE::vec4 translation = GetWorldTransform().row3;

	m_iNumVerts = m_iVertsWidth * m_iVertsLength;

	int iNumTris = ((m_iVertsWidth-1) * (m_iVertsLength-1)) * 2;
	m_iNumIndices = iNumTris * 3;

	for( int z = 0; z < m_iVertsLength; ++z )
	{
		for( int x = 0; x < m_iVertsWidth; ++x )
		{
			m_aoVertices.push_back( AIE::Vertex() );

			float xPos = translation.x;
			float yPos = translation.y;
			float zPos = translation.z;

			xPos += x == 0 ? 0 : m_fWidth * (static_cast<float>(x)/static_cast<float>(m_iVertsWidth-1));
			zPos += z == 0 ? 0 : m_fLength * (static_cast<float>(z)/static_cast<float>(m_iVertsLength-1));

			yPos = PerlinNoise2D( x*(1.f/m_iVertsWidth), z*(1.f/m_iVertsLength), 0.75f, 6 ) * m_fHeightScale;

			m_aoVertices[z*m_iVertsLength + x].position = AIE::vec4( xPos-fHalfWidth, yPos, zPos-fHalfLength, 1.0f );
		
			float u = x == 0 ? 0 : (xPos - translation.x)/m_fWidth;
			float v = z == 0 ? 0 : (zPos - translation.z)/m_fLength;
			m_aoVertices[z*m_iVertsLength + x].uv = AIE::vec2( u, v );
		}
	}

	for( int z = 0; z < m_iVertsLength-1; ++z )
	{
		for( int x = 0; x < m_iVertsWidth-1; ++x )
		{
			m_auiIndex.push_back( (z*m_iVertsWidth)+x );
			m_auiIndex.push_back( ((z*m_iVertsWidth)+x) + 1 );
			m_auiIndex.push_back( ((z+1)*m_iVertsWidth)+x );
		
			m_auiIndex.push_back( ((z*m_iVertsWidth)+x) + 1 );
			m_auiIndex.push_back( ((z+1)*m_iVertsWidth)+x + 1 );
			m_auiIndex.push_back( ((z+1)*m_iVertsWidth)+x );
		}
	}

	CreateBuffers();
}

void TerrainNode::Update( float a_fDeltaTime )
{
}

void TerrainNode::Draw()
{
	MeshNode::Draw();
}
