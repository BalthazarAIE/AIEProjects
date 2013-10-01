#include "GSLab07.h"
#include "CApplication.h"
#include "CRenderManager.h"

GSLab07::GSLab07(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poSkybox = new Skybox( 900.f );
	m_poSkybox->SetTexture( LoadTexture("./images/skybox_purple.png") );
	m_poSkybox->SetColour( AIE::vec4( 1.0f, 0.4f, 0.f, 1.0f) );

	m_poTerrain = new TerrainNode(400.f, 400.f, 160.f, 100, 100, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTerrain->SetColour( AIE::vec4( 0.45f, 0.f, .2f, 1.f ) );

	m_poTitle = new PlaneNode( 30.f, 30.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab07.png") );
	m_qPlaneRot.CreateRotation( PI/2, AIE::vec4(1.f,0.f,0.f,0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_qPlaneRot.CreateRotation( PI, AIE::vec4(0.f,0.f,1.f,0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(60.f, 30.f, 175.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_poGlass = new PlaneNode( 33.f, 62.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poGlass->SetColour( AIE::vec4(0.f,0.6f,0.2f,0.8f) );
	m_qPlaneRot.CreateRotation( PI/2, AIE::vec4(1.f,0.f,0.f,0.f) );
	m_poGlass->RotateNode( m_qPlaneRot );
	m_poGlass->TranslateNode( AIE::vec4( 0.f, 0.f, 180.f, 0.f ) );
	m_poGlass->UpdateBuffers();

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poSkybox		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTerrain	);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poGlass		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle		);

	m_pParticleManager = new ParticleManager();
	m_pParticleManager->Init();
	m_pParticleManager->CreateSystem( "CUBES" );

	m_pApp->GetRenderManager()->AddParticleManager( m_eStateID, m_pParticleManager );
}

GSLab07::~GSLab07()
{
	delete m_pParticleManager;
	m_pParticleManager = nullptr;

	delete m_poTerrain;
	m_poTerrain = nullptr;

	delete m_poTitle;
	m_poTitle = nullptr;

	delete m_poGlass;
	m_poGlass = nullptr;

	delete m_poSkybox;
	m_poSkybox = nullptr;
}

void GSLab07::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,0.f, 350.f,1.f), AIE::vec4(0.f,0.f,-1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );	

	printf( "\n\n------------------------------------------------\n"
			"Lab 07 - Post-Processing\n\n"

			"This scene is first rendered to a buffer, and a bump map\n" 
			"is applied to create the refracted glass of the window\n\n"

			"The entire scene is then blurred using Gaussian Blur,\n"
			"which requires two passes.\n\n"

			"All light properties are passed into the shader as uniforms.\n\n"

			"Relevant code can be found in:\n\n"

			"GSLab07.h & .cpp\n"
			"'refraction' shaders\n"
			"'gaussian' shaders\n"
			"'fullscreen_quad' shaders\n"
			"DrawLab07() function in CRenderManager.cpp\n"
			"------------------------------------------------\n" );
}

void GSLab07::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab07::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );

	m_pParticleManager->Update( a_fDeltaTime );
}	 

void GSLab07::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}