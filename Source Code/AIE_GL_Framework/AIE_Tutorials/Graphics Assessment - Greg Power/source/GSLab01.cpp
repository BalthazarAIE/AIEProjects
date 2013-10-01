#include "GSLab01.h"
#include "CApplication.h"
#include "CRenderManager.h"

GSLab01::GSLab01(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poCamera = new Camera();

	m_poTitlePlane = new PlaneNode(20.f, 20.f, 2, 2, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poTitlePlane->SetTexture( LoadTexture("./images/lab01.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitlePlane->RotateNode( m_qPlaneRot );
	m_poTitlePlane->TranslateNode( AIE::vec4(0.f, 8.f, -40.f, 0.f) );
	m_poTitlePlane->UpdateBuffers();

	m_poWaterPlane = new PlaneNode(100.f, 100.f, 100, 100, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poWaterPlane->SetTexture( LoadTexture("./images/water.png") );
	
	m_poCobbleStonePlane = new PlaneNode(100.f, 100.f, 100, 100, AIE::vec4(0.f, -3.f, 0.f, 1.f));
	m_poCobbleStonePlane->SetTexture( LoadTexture("./images/cobblestone.jpg") );

	m_poWallPlane01 = new PlaneNode(100.f, 45.f, 2, 2, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poWallPlane01->SetTexture( LoadTexture("./images/dungeon_wall2.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poWallPlane01->RotateNode( m_qPlaneRot );
	m_poWallPlane01->TranslateNode( AIE::vec4(0.f, 19.5f, 50.f, 0.f) );
	m_poWallPlane01->UpdateBuffers();

	m_poWallPlane02 = new PlaneNode(100.f, 45.f, 2, 2, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poWallPlane02->SetTexture( LoadTexture("./images/dungeon_wall2.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(0.f, 1.f, 0.f, 0.f) );
	m_poWallPlane02->RotateNode( m_qPlaneRot );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(0.f, 0.f, 1.f, 0.f) );
	m_poWallPlane02->RotateNode( m_qPlaneRot );
	m_poWallPlane02->TranslateNode( AIE::vec4(-50.f, 19.5f, 0.f, 0.f) );
	m_poWallPlane02->UpdateBuffers();

	m_poWallPlane03 = new PlaneNode(100.f, 45.f, 2, 2, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poWallPlane03->SetTexture( LoadTexture("./images/dungeon_wall2.png") );
	m_qPlaneRot.CreateRotation(PI/2, AIE::vec4(0.f, 1.f, 0.f, 0.f) );
	m_poWallPlane03->RotateNode( m_qPlaneRot );
	m_qPlaneRot.CreateRotation(PI/2, AIE::vec4(0.f, 0.f, 1.f, 0.f) );
	m_poWallPlane03->RotateNode( m_qPlaneRot );
	m_poWallPlane03->TranslateNode( AIE::vec4(50.f, 19.5f, 0.f, 0.f) );
	m_poWallPlane03->UpdateBuffers();

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poWallPlane01		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poWallPlane02		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poWallPlane03		);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitlePlane			);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poWaterPlane			);
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poCobbleStonePlane	);
}

GSLab01::~GSLab01()
{
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poWallPlane01			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poWallPlane02			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poWallPlane03			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poTitlePlane			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poWaterPlane			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poCobbleStonePlane	);

	delete m_poWallPlane03;
	m_poWallPlane03 = nullptr;

	delete m_poWallPlane02;
	m_poWallPlane02 = nullptr;

	delete m_poWallPlane01;
	m_poWallPlane01 = nullptr;

	delete m_poCobbleStonePlane;
	m_poCobbleStonePlane = nullptr;

	delete m_poWaterPlane;
	m_poWaterPlane = nullptr;

	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab01::Load()
{
	m_poCamera->SetCameraPosition( AIE::vec4(0.f, 7.f, -80.f, 1.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );

	printf( "\n\n------------------------------------------------\n"
			"Lab 01 - Vertex Shaders\n\n" 
			"The 'water' is a plane with 10,000 vertices.\n"
			"The ripples are created in the vertex shader\n"
			"(lab01_water_vertex.glsl) using a sine wave.\n\n"

			"Relevant code can be found in:\n\n"

			"PlaneNode.h & .cpp\n"
			"GSLab01.h & .cpp\n"
			"'lab01_water' shaders\n"
			"DrawLab01() in CRenderManager.cpp\n" 
			"------------------------------------------------\n");
}	 
	 
void GSLab01::Unload()
{
}	 
	 
void GSLab01::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );

	AIE::vec4 trans = AIE::vec4(0.f,0.f,0.f,0.f);
	trans.y += cos( m_fTimer ) / 620.f;
	m_poTitlePlane->TranslateNode( trans );
	m_poTitlePlane->UpdateBuffers();
}	 
	 
void GSLab01::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}