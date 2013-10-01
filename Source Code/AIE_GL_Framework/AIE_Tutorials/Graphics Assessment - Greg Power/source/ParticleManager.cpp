#include "ParticleManager.h"

#include "tinyxml.h"
#include "tinystr.h"
#include <string>

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
	m_SysIter = m_aActiveSystems.begin();

	while( m_SysIter != m_aActiveSystems.end() )
	{
		delete (*m_SysIter);
		(*m_SysIter) = nullptr;
		m_SysIter = m_aActiveSystems.erase(m_SysIter);
	}
}

void ParticleManager::Init()
{
	const char* szFilename = "./scripts/particle_settings.xml";
	TiXmlDocument doc( szFilename );
	bool bLoadedOkay = doc.LoadFile();

	if( !bLoadedOkay )
	{
		printf("Error Loading XML: %s\n", doc.ErrorDesc() );
		return;
	}

	TiXmlNode *pRoot = doc.FirstChild("ParticleSettings")->ToElement();

	TiXmlElement *pSetting = pRoot->FirstChildElement();

	while( pSetting != NULL )
	{
		std::string name = pSetting->Attribute("name");
		//name += '\0';
		SystemData newSystem;

		TiXmlElement *pValue = pSetting->FirstChildElement();
		while( pValue != NULL )
		{
			int id = atoi( pValue->Attribute("id") );

			switch( id )
			{
			case 1:
				newSystem.iNumParticles = atoi( pValue->Attribute("val") );
				break;
			case 2:
				newSystem.vEmitterPos	= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														1.0f);
				break;
			case 3:
				newSystem.vEmitterSize	= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														0.0f);
				break;
			case 4:
				newSystem.iEmissionRate	= atoi( pValue->Attribute("val") );
				break;
			case 5:
				newSystem.vPSizeMin		= AIE::vec2(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ) );
				break;
			case 6:
				newSystem.vPSizeMax		= AIE::vec2(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ) );
				break;
			case 7:
				newSystem.vPVelocityMin	= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														0.0f);
				break;
			case 8:
				newSystem.vPVelocityMax	= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														0.0f);
				break;
			case 9:
				newSystem.vGravity		= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														0.0f);
				break;
			case 10:
				newSystem.vWind			= AIE::vec4(	(float)atof( pValue->Attribute("x") ),
														(float)atof( pValue->Attribute("y") ),
														(float)atof( pValue->Attribute("z") ),
														0.0f);
				break;
			case 11:
				newSystem.vEnergy		= AIE::vec2(	(float)atof( pValue->Attribute("min") ),
														(float)atof( pValue->Attribute("max") ) );
				break;
			case 12:
				newSystem.bLoop			= atoi( pValue->Attribute("val") );
				break;
			case 13:
				newSystem.sFilename		= pValue->Attribute("filename");
				break;
			case 14:
				newSystem.vColour		= AIE::vec4(	(float)atof( pValue->Attribute("r") ),
														(float)atof( pValue->Attribute("g") ),
														(float)atof( pValue->Attribute("b") ),
														(float)atof( pValue->Attribute("a") ) );
				break;
			case 15:
				newSystem.b3D			= atoi( pValue->Attribute("val") );
				break;
			}

			pValue = pValue->NextSiblingElement();
		}

		m_aSystemTypes[ name ] = newSystem;

		pSetting = pSetting->NextSiblingElement();
	}

}	 
	 
bool ParticleManager::CreateSystem( std::string a_sName )
{
	SystemData data;
	try{
		data = m_aSystemTypes.at( a_sName );
	}
	catch(const std::out_of_range& oor)
	{
		printf("No system type registered under '%s'", a_sName );
		return false;
	}

	ParticleSystem* sys = new ParticleSystem();
	sys->Init( &data );

	m_aActiveSystems.push_back( sys );

	return true;
}	 
	 
void ParticleManager::Update( float a_fDeltaTime )
{	
	m_SysIter = m_aActiveSystems.begin();

	while( m_SysIter != m_aActiveSystems.end() )
	{
		(*m_SysIter)->Update( a_fDeltaTime );
		++m_SysIter;
	}
}	 
	 
void ParticleManager::Draw( AIE::mat4& a_projectionMat, AIE::mat4& a_viewMat, AIE::mat4& a_modelMat, AIE::mat4& a_vCameraMat )
{
	m_SysIter = m_aActiveSystems.begin();

	while( m_SysIter != m_aActiveSystems.end() )
	{	
		(*m_SysIter)->Draw( a_projectionMat, a_viewMat, a_modelMat, a_vCameraMat );
		++m_SysIter;
	}
}