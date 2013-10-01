#include "GSLab03.h"
#include "CApplication.h"
#include "CRenderManager.h"
#include "ParticleSystem.h"

GSLab03::GSLab03(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poSkyBox = new Skybox( 300.f );
	m_poSkyBox->SetTexture( LoadTexture("./images/skybox_purple.png") );

	m_poTitle = new PlaneNode( 10.f, 10.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab03.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(-8.f, 0.f, 10.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_poParticleManager = new ParticleManager();
	m_poParticleManager->Init();
	m_poParticleManager->CreateSystem( "MANA" );

	m_poSphere		= new IcosphereNode( 1.0f, AIE::vec4(0.f,0.f,0.f,1.f) );

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poSkyBox			);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle			);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poSphere			);
	m_pApp->GetRenderManager()->AddParticleManager( m_eStateID, m_poParticleManager );
}

GSLab03::~GSLab03()
{
	delete m_poSkyBox;
	m_poSkyBox = nullptr;

	delete m_poTitle;
	m_poTitle = nullptr;

	delete m_poSphere;
	m_poSphere = nullptr;

	delete m_poParticleManager;
	m_poParticleManager = nullptr;
}

void GSLab03::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,0.f,-50.f,1.f), AIE::vec4(0.f,0.f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );

	printf( "\n\n------------------------------------------------\n"
			"Lab 03 - Geometry Shaders\n\n"

			"The triangles of the icosahedron mesh are being pushed\n"
			"out using the geometry shader ('lab03_geometry.glsl').\n\n"

			"The particles are being passed in as points, and are\n"
			"converted to particles using billboarding (particle_2d_geometry.glsl).\n\n"

			"Relevant code can be found in:\n\n"

			"GSLab03.h & .cpp\n"
			"'lab03' shaders\n"
			"'particle_2d' shaders\n"
			"DrawLab03() function in CRenderManager.cpp\n"
			"------------------------------------------------\n" );

}

void GSLab03::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab03::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );

	Quaternion quat;
	quat.CreateRotation( PI/8 * a_fDeltaTime, AIE::vec4(0.f,1.f,0.f,1.f) );
	m_poSphere->RotateNode( quat );
	m_poSphere->UpdateBuffers();

	m_poParticleManager->Update( a_fDeltaTime );
}	 

void GSLab03::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}