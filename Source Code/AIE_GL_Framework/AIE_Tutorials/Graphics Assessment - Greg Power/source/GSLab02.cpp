#include "GSLab02.h"
#include "CApplication.h"
#include "CRenderManager.h"

GSLab02::GSLab02(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	m_poRoom = new Skybox(60.f );
	m_poRoom->SetTexture( LoadTexture( "./images/wallpaper1.png" ) );
	m_poRoom->SetSecondaryTexture( LoadTexture( "./images/wallpaper_hidden1.png" ) );

	m_poTitle = new PlaneNode( 30.f, 20.f, 20, 20, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab02.png") );
	m_poTitle->SetSecondaryTexture( LoadTexture("./images/lab02_hidden.png") );
	m_qPlaneRot.CreateRotation( -PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode(m_qPlaneRot);
	m_poTitle->TranslateNode( AIE::vec4(0.f, -12.f, 0.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_poPainting01 = new PlaneNode( 10.f, 7.2f, 20, 20, AIE::vec4(0.f, 0.f, 0.f, 1.f) );
	m_poPainting01->SetTexture( LoadTexture("./images/spainPlane011.png") );
	m_poPainting01->SetSecondaryTexture( LoadTexture("./images/spainPlane01_hidden1.png") );
	m_qPlaneRot.CreateRotation( -PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poPainting01->RotateNode(m_qPlaneRot);
	m_poPainting01->TranslateNode( AIE::vec4(-16.f, 0.f, 0.f, 0.f) );
	m_poPainting01->UpdateBuffers();

	m_poPainting02 = new PlaneNode( 10.f, 8.9f, 20, 20, AIE::vec4(0.f, 0.f, 0.f, 1.f) );
	m_poPainting02->SetTexture( LoadTexture("./images/spainPlane021.png") );
	m_poPainting02->SetSecondaryTexture( LoadTexture("./images/spainPlane02_hidden1.png") );
	m_poPainting02->RotateNode(m_qPlaneRot);
	m_poPainting02->TranslateNode( AIE::vec4(16.f, 0.f, 0.f, 0.f) );
	m_poPainting02->UpdateBuffers();

	m_poPainting03 = new PlaneNode( 10.f, 11.7f, 20, 20, AIE::vec4(0.f, 0.f, 0.f, 1.f) );
	m_poPainting03->SetTexture( LoadTexture("./images/spainPlane031.png") );
	m_poPainting03->SetSecondaryTexture( LoadTexture("./images/spainPlane03_hidden1.png") );
	m_poPainting03->RotateNode(m_qPlaneRot);
	m_poPainting03->TranslateNode( AIE::vec4(0.f, 0.f, 0.f, 0.f) );
	m_poPainting03->UpdateBuffers();
	
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poRoom );
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle );
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poPainting01 );
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poPainting02 );
	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poPainting03 );
}

GSLab02::~GSLab02()
{
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poRoom			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poTitle			);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poPainting01		);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poPainting02		);
	m_pApp->GetRenderManager()->RemoveNode( m_eStateID, m_poPainting03		);

	delete m_poPainting03;
	m_poPainting03 = nullptr;

	delete m_poPainting02;
	m_poPainting02 = nullptr;

	delete m_poPainting01;
	m_poPainting01 = nullptr;

	delete m_poTitle;
	m_poTitle = nullptr;

	delete m_poRoom;
	m_poRoom = nullptr;

}

void GSLab02::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,-4.f,-130.f,1.f), AIE::vec4(0.f,0.f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );

	printf( "\n\n------------------------------------------------\n"
			"Lab 02 - Fragment Shaders\n\n"

			"Move closer to the paintings.\n\n"

			"The textures are blended depending on the distance\n"
			"from the camera (the camera position is passed into\n"
			"the fragment shader as a uniform).\n\n"
			
			"Total time is passed into the vertex shader to create\n"
			"the wavey effect.\n\n"
			
			"Relevant code can be found in:\n\n"
			
			"PlaneNode.h & .cpp\n"
			"GSLab02.h & .cpp\n"
			"'lab02' shaders\n"
			"DrawLab02() function in CRenderManager.cpp\n"
			"------------------------------------------------\n");
}	 
	 
void GSLab02::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}	 
	 
void GSLab02::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );
}	 
	 
void GSLab02::Draw()
{
	m_poRoom->Draw();
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}