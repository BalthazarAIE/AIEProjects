#include "GSLab04.h"
#include "CApplication.h"
#include "CRenderManager.h"

GSLab04::GSLab04(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poTitle = new PlaneNode( 10.f, 10.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab04.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(0.f, 190.f, -180.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_poTerrain = new PlaneNode( 500.f, 500.f, 100, 100, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTerrain->SetTexture( LoadTexture("./images/perlin_noise.png") );
	m_poTerrain->SetDisplacementTexture( LoadTexture("./images/perlin_noise.png") );

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTerrain );
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle );
}

GSLab04::~GSLab04()
{
	delete m_poTerrain;
	m_poTerrain = nullptr;

	delete m_poTitle;
	m_poTitle = nullptr;
}

void GSLab04::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,200.f,-200.f,1.f), AIE::vec4(0.f,-0.5f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );

	printf( "\n\n------------------------------------------------\n"
			"Lab 04 - Tessellation Shaders\n\n"

			"The terrain is a plane with 10,000 vertices.\n\n"

			"The plane is subdivided based on the distance from the camera\n"
			"(lab04_tess_control.glsl).\n\n"

			"In the tessellation evaluation shader, the plane is raised\n"
			"along the Y-axis using a height map (lab04_tess_eval.glsl).\n\n"

			"Relevant code can be found in:\n\n"

			"GSLab04.h & .cpp\n"
			"'lab04' shaders\n"
			"DrawLab04() function in CRenderManager.cpp\n"
			"------------------------------------------------\n" );
}

void GSLab04::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab04::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );
}	 

void GSLab04::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}