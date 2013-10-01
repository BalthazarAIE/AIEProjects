#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include <vector>
#include <map>
#include <string>
#include "Utilities.h"
#include "ParticleSystem.h"

class ParticleManager
{
public:
									ParticleManager();
									~ParticleManager();

	void							Init();
	bool							CreateSystem( std::string a_sName );
	std::vector<ParticleSystem*>	GetActiveEmitters() { return m_aActiveSystems; }
	
	void							Update( float a_fDeltaTime );
	void							Draw( AIE::mat4& a_projectionMat, AIE::mat4& a_viewMat, AIE::mat4& a_modelMat, AIE::mat4& a_vCameraMat );

private:
	std::vector<ParticleSystem*>	m_aActiveSystems;
	std::vector<ParticleSystem*>::iterator m_SysIter;
	std::map< std::string, SystemData> m_aSystemTypes;
};

#endif