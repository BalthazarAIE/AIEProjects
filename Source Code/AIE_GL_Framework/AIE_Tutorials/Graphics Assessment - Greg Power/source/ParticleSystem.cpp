#include "ParticleSystem.h"

#include "MathHelper.h"
#include "Utilities.h"
#include <random>

ParticleSystem::ParticleSystem()
{
	m_fTimer = 0.f;
}

ParticleSystem::~ParticleSystem()
{
	if( m_iTextureID != 0 )
		glDeleteTextures(1,&m_iTextureID);
	glDeleteVertexArrays(1, &m_uiVAO);
	glDeleteBuffers(1, &m_uiVBO);
}

void ParticleSystem::Init( SystemData* a_oData )
{
	m_vEmitterPosition		= a_oData->vEmitterPos;
	m_vEmitterSize			= a_oData->vEmitterSize;
	m_iEmissionsPerSec		= a_oData->iEmissionRate;
	m_fNumToRelease			= 0.f;
	m_iSystemType			= 0;
	m_iNumParticlesAlive	= a_oData->iNumParticles;
	m_vVelocityMin			= a_oData->vPVelocityMin;
	m_vVelocityMax			= a_oData->vPVelocityMax;
	m_vGravity				= a_oData->vGravity;
	m_vWind					= a_oData->vWind;
	m_oPSizeMin.size		= a_oData->vPSizeMin;
	m_oPSizeMax.size		= a_oData->vPSizeMax;
	m_fEnergyMin			= a_oData->vEnergy.x;
	m_fEnergyMax			= a_oData->vEnergy.y;
	m_vColour				= a_oData->vColour;
	m_bIs3D					= a_oData->b3D;
	std::string filename	= "./images/";
	filename				+= a_oData->sFilename;
	m_iTextureID			= AIE::LoadTexture( filename.c_str() );

	for( int i = 0; i < m_iNumParticlesAlive; ++i )
	{
		Particle p;
		p.vPosition		= m_vEmitterPosition + AIE::v4Rand( -m_vEmitterSize/2, m_vEmitterSize/2 );
		p.vOldPosition	= m_vEmitterPosition;
		p.vVelocity		= AIE::v4Rand(m_vVelocityMin, m_vVelocityMax );
		p.oSize.width	= AIE::fRand( m_oPSizeMin.width, m_oPSizeMax.width );
		p.oSize.height	= AIE::fRand( m_oPSizeMin.height, m_oPSizeMax.height );
		p.fEnergy		= 0.f;
		p.fAlpha		= (1.0f / m_fEnergyMax ) * p.fEnergy;
		p.vColour		= m_vColour;
		p.bIsDead		= true;
		
		m_aParticleArray.push_back( p );
	}

	//// load shader
	//const char* aszInputs[] = { "Position", "Size", "Alpha" };
	//const char* aszOutputs[] = { "outColour" };

	//m_iShaderID = AIE::LoadShader( 3, aszInputs, 0, aszOutputs,
	//	"./shaders/ParticleSystem_Vertex.glsl",
	//	"./shaders/ParticleSystem_Pixel.glsl",
	//	"./shaders/ParticleSystem_Geometry.glsl" );

	////GLuint ProjectionID	= glGetUniformLocation( m_iShaderID,	"Projection"	);
	////GLuint ViewID			= glGetUniformLocation( m_iShaderID,	"View"			);
	////GLuint ModelID		= glGetUniformLocation( m_iShaderID,	"Model"			);

	//// set the texture to use slot 0 in the shader
	//GLuint texUniformID0 = glGetUniformLocation( m_iShaderID, "diffuseTexture" );
	//glUniform1i(texUniformID0,0);

	// create and bind buffers to a vertex array object
	glGenBuffers		(1, &m_uiVBO);
	glGenVertexArrays	(1, &m_uiVAO);

	glBindVertexArray	(m_uiVAO);
	glBindBuffer		(GL_ARRAY_BUFFER, m_uiVBO);

	// unbind vertex array
	glBindVertexArray(0);
}

void ParticleSystem::Update( float a_fDeltaTime )
{
	m_fTimer += a_fDeltaTime;
	m_vWind.x = sin( m_fTimer * 0.5f );


	m_fNumToRelease += m_iEmissionsPerSec * a_fDeltaTime;

	std::vector<Particle>::iterator iter = m_aParticleArray.begin();

	while( iter != m_aParticleArray.end() )
	{
		if( iter->bIsDead && m_fNumToRelease >= 1 )
		{
			iter->bIsDead	= false;
			iter->vPosition	= m_vEmitterPosition + AIE::v4Rand( -m_vEmitterSize/2, m_vEmitterSize/2 );
			iter->fEnergy	= AIE::fRand( m_fEnergyMin, m_fEnergyMax );
			iter->vVelocity	= AIE::v4Rand(m_vVelocityMin, m_vVelocityMax );

			--m_fNumToRelease;
		}

		iter->vOldPosition	= iter->vPosition;
		iter->vVelocity		+= m_vGravity * a_fDeltaTime;
		iter->vVelocity		+= m_vWind * a_fDeltaTime;
		iter->vPosition		+= iter->vVelocity * a_fDeltaTime;
		iter->fAlpha		= (1.0f / m_fEnergyMax) * iter->fEnergy;
		if( !m_bIs3D && iter->fAlpha > 0.4f )
			iter->fAlpha = 0.4f;

		iter->fEnergy -= a_fDeltaTime;
		if( iter->fEnergy <= 0 )
			iter->bIsDead	= true;

		++iter;
	}

	if( m_bIs3D )
	{
		glBindVertexArray(m_uiVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);

		glBufferData(GL_ARRAY_BUFFER, m_aParticleArray.size() * sizeof(Particle),	&m_aParticleArray[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 16);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 24);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 60);

		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(m_uiVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);

		glBufferData(GL_ARRAY_BUFFER, m_aParticleArray.size() * sizeof(Particle),	&m_aParticleArray[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 16);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 24);

		glBindVertexArray(0);
	}
	
}

void ParticleSystem::Draw( AIE::mat4& a_projectionMat, AIE::mat4& a_viewMat, AIE::mat4& a_modelMat, AIE::mat4& a_vCameraMat )
{
	if( m_bIs3D )
	{
		glEnable(GL_POINTS);
		glPointSize( 2.0f );

		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glBindVertexArray( m_uiVAO );
		glDrawArrays( GL_POINTS, 0, m_aParticleArray.size() );

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
	else
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_iTextureID );

		glEnable(GL_POINTS);
		glPointSize( 2.0f );

		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glBindVertexArray( m_uiVAO );
		glDrawArrays( GL_POINTS, 0, m_aParticleArray.size() );

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}