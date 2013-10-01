#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "Particle.h"
#include <vector>
#include <string>

struct SystemData
{
	int			iNumParticles;
	AIE::vec4	vEmitterPos;
	AIE::vec4	vEmitterSize;
	int			iEmissionRate;
	AIE::vec2	vPSizeMin;
	AIE::vec2	vPSizeMax;
	AIE::vec4	vPVelocityMin;
	AIE::vec4	vPVelocityMax;
	AIE::vec4	vGravity;
	AIE::vec4	vWind;
	AIE::vec2	vEnergy;
	AIE::vec4	vColour;

	std::string	sFilename;
	bool		bLoop;
	bool		b3D;

};

class ParticleSystem
{
public:
							ParticleSystem();
							~ParticleSystem();
	bool					Is3D() { return m_bIs3D; }
	virtual void			Init( SystemData* a_oData );
	virtual void			Update( float a_fDeltaTime );
	virtual void			Draw( AIE::mat4& a_projectionMat, AIE::mat4& a_viewMat, AIE::mat4& a_modelMat, AIE::mat4& a_vCameraMat );

protected:
	GLuint					m_uiVAO, m_uiVBO;
	//////GLuint					m_FBO, m_FBT, m_FBD;
	//////GLuint					m_iRenderBufferID;

	AIE::vec4				m_vEmitterPosition;
	AIE::vec4				m_vEmitterSize;
	int						m_iEmissionsPerSec;
	float					m_fNumToRelease;
	std::vector<Particle>	m_aParticleArray;
	GLuint					m_iTextureID;
	int						m_iSystemType;
	int						m_iNumParticlesAlive;
	AIE::vec4				m_vVelocityMin;
	AIE::vec4				m_vVelocityMax;
	AIE::vec4				m_vGravity;
	AIE::vec4				m_vWind;
	PSize					m_oPSizeMin;
	PSize					m_oPSizeMax;
	float					m_fEnergyMin;
	float					m_fEnergyMax;
	AIE::vec4				m_vColour;
	GLuint					m_iShaderID;
	bool					m_bIs3D;

	float					m_fTimer;
		
};

#endif