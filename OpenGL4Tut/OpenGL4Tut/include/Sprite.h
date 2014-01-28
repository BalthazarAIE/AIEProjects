#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Utilities.h"
#include "Quad.h"
#include <SOIL.h>

class Sprite: public Quad
{
public:
	Sprite(void);
	~Sprite(void);
Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, tbyte::Vector4 a_v4Color );
	void Draw();
	
	
	void SetPosition( int a_iX, int a_iY );
	void SetPosition( float* a_fVec );
	void GetPosition( int& a_iX, int& a_iY );

	void SetVertexData( Vertex* a_vertexData );
	const Vertex* GetVertexData() const;

	void SetSpriteMatrix( float* a_fm4 );

	void SetOrigin( const tbyte::Vector2 & a_v2Origin );
	void GetOrigin( tbyte::Vector2 & a_v2Origin ) const ;

	void SetSize( float a_iWidth, float a_iHeight );
	void GetSize( float& a_iWidth, float& a_iHeight );

	void SetSpriteID( unsigned int a_uiSpriteID );
	void GetSpriteID( unsigned int& a_uiSpriteID );



private:
	
	Vertex m_aoVerts[4];

	mat4 m_m4Matrix;
	tbyte::Vector2 m_v2Scale;
	tbyte::Vector3 m_v3Position;
	tbyte::Vector4 m_v4SpriteColor;



	tbyte::Vector2 m_minUVCoords;
	tbyte::Vector2 m_maxUVCoords;
	tbyte::Vector2 m_uvScale;
	tbyte::Vector2 m_uvOffset;	


	unsigned int m_uiTexture;
	
	//used later
	unsigned int	m_uSourceBlendMode;
	unsigned int	m_uDestinationBlendMode;
	int tex_loc;
	int matrix_location;



	
};


inline void Sprite::SetPosition( int a_iX, int a_iY )
{
	m_m4Matrix.row3 = tbyte::Vector4( (float)a_iX, (float)a_iY, 0.f, 1.f );
}

inline void Sprite::SetPosition( float* a_fVec )
{
	m_m4Matrix.row3 = tbyte::Vector4( a_fVec[0], a_fVec[1], 0.f, 1.f );
}

inline void Sprite::SetSpriteMatrix( float* a_fm4 )
{
	memcpy(m_m4Matrix, a_fm4, sizeof(float) * 16 );
}

inline void Sprite::GetPosition( int& a_iX, int& a_iY )
{
	a_iX = (int)m_m4Matrix.row3.m_fX;
	a_iY = (int)m_m4Matrix.row3.m_fY;
}

inline void Sprite::SetSize(float a_iWidth, float a_iHeight )
{
	m_v2Scale = tbyte::Vector2( a_iWidth, a_iHeight);
}

inline void Sprite::GetSize( float& a_iWidth, float& a_iHeight )
{
	a_iWidth = (int)m_v2Scale.m_fX;
	a_iHeight = (int)m_v2Scale.m_fY;
}

inline void	Sprite::SetVertexData( Vertex* a_vertexData )
{
	memcpy( &m_aoVerts, a_vertexData, sizeof(Vertex) * 4 );
}

inline const Vertex* Sprite::GetVertexData() const
{
	return static_cast<const Vertex*>( m_aoVerts );
}


#endif
