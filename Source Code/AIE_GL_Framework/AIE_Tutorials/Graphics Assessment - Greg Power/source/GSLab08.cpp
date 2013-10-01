#include "GSLab08.h"
#include "CApplication.h"
#include "CRenderManager.h"
#include "FBXLoader.h"

GSLab08::GSLab08(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poSkyBox = new Skybox( 1000.f );
	m_poSkyBox->SetTexture( LoadTexture("./images/skybox_mars.png") );

	m_poTerrain = new TerrainNode( 1000.f, 1000.f, 100.f, 500, 500, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTerrain->SetTexture( LoadTexture("./images/cracked_mud.jpg") );

	m_poIcosphere = new IcosphereNode( 5.f, AIE::vec4(0.f,10.f,0.f,1.f) );

	m_poTitle = new PlaneNode( 40.f, 40.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab08.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(0.f, 20.f, 0.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poSkyBox		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTerrain	);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poIcosphere	);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle		);
}

GSLab08::~GSLab08()
{
	delete m_poIcosphere;
	m_poIcosphere = nullptr;

	delete m_poTerrain;
	m_poTerrain = nullptr;

	delete m_poTitle;
	m_poTitle = nullptr;

	delete m_poSkyBox;
	m_poSkyBox = nullptr;
}

void GSLab08::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,20.f,-180.f,1.f), AIE::vec4(0.f,0.f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );	

	printf( "\n\n------------------------------------------------\n"
			"Lab 08 - Height Maps\n\n"
			
			"This terrain is generated using a 2D Perlin Noise function.\n\n"
			
			"Relevant code can be found in:\n\n"
			
			"TerrainNode.h & .cpp\n"
			"PerlinNoise2D.h\n"
			"GSLab08.h & .cpp\n"
			"DrawLab08() function in CRenderManager.cpp\n"
			"------------------------------------------------\n" );
}

void GSLab08::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab08::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );

	Quaternion quat;
	quat.CreateRotation( PI/16 * a_fDeltaTime, AIE::vec4(0.f,1.f,0.f,1.f) );

	m_poIcosphere->RotateNode( quat );
	m_poIcosphere->UpdateBuffers();
}	 

void GSLab08::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}