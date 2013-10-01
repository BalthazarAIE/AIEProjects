#include "GSLab05.h"
#include "CApplication.h"
#include "CRenderManager.h"

#include "Utilities.h"

GSLab05::GSLab05(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	// load FBX scene
	m_oScene.Load("./scenes/SoulSpear.fbx");
	InitFBXSceneResources(&m_oScene);

	m_poTitle = new PlaneNode( 4.f, 4.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab05.png") );
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(3.f, 2.f, 1.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle );
}

GSLab05::~GSLab05()
{
	DestroyFBXSceneResources(&m_oScene);
	m_oScene.Unload();

	delete m_poTitle;
	m_poTitle = nullptr;
}

void GSLab05::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,2.f,-10.f,1.f), AIE::vec4(0.f,0.f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );
	m_pApp->GetRenderManager()->SetFBXScene( m_oScene );

	printf( "\n\n------------------------------------------------\n"
		"Lab 05 and 06 - Diffuse and Specular Lighting\n\n"

		"The the SoulSpear model is lit by ambient lighting,\n" 
		"a white directional light, a red point light, and a\n"
		"white spot light (check the back of the model).\n\n"

		"Each light type provides diffuse and specular lighting.\n"
		"Specular lighting is calculated using the specular texture,\n"
		"and the light's colour.\n\n"

		"All light properties are passed into the shader as uniforms.\n\n"

		"Relevant code can be found in:\n\n"

		"GSLab05.h & .cpp\n"
		"'normalmap' shaders\n"
		"DrawLab05() function in CRenderManager.cpp\n"
		"------------------------------------------------\n" );
}

void GSLab05::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab05::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );
}	 

void GSLab05::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}

//////////////////////////////////////////////////////////////////////////
void GSLab05::InitFBXSceneResources(FBXScene* a_pScene)
{
	unsigned int meshCount = a_pScene->GetMeshCount();
	unsigned int matCount = a_pScene->GetMaterialCount();

	for ( unsigned int i = 0 ; i < meshCount ; ++i )
	{
		FBXMeshNode* pMesh = a_pScene->GetMeshByIndex(i);

		RenderObject* ro = new RenderObject;
		pMesh->m_userData = ro;

		glGenBuffers(		1, &ro->VBO);
		glGenBuffers(		1, &ro->IBO);
		glGenVertexArrays(	1, &ro->VAO);

		glBindVertexArray(ro->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, ro->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro->IBO);

		glBufferData(GL_ARRAY_BUFFER,			pMesh->m_vertices.size() * sizeof(FBXVertex),	pMesh->m_vertices.data(),	GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,	pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(),	GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); // pos
		glEnableVertexAttribArray(1); // normal
		glEnableVertexAttribArray(2); // tangent
		glEnableVertexAttribArray(3); // binormal
		glEnableVertexAttribArray(4); // indices of affecting bones
		glEnableVertexAttribArray(5); // weighting 
		glEnableVertexAttribArray(6); // uv
		glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::PositionOffset	);
		glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::NormalOffset		);
		glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TangentOffset		);
		glVertexAttribPointer( 3, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::BiNormalOffset	);
		glVertexAttribPointer( 4, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::IndicesOffset		);
		glVertexAttribPointer( 5, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::WeightsOffset		);
		glVertexAttribPointer( 6, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::UVOffset			);
		glBindVertexArray(0);
	}

	for(unsigned int i = 0; i < matCount; ++i)
	{
		FBXMaterial* pMaterial = m_oScene.GetMaterialByIndex(i);

		for(unsigned int j = 0; j < FBXMaterial::TextureTypes_Count; ++j)
		{
			if (strlen(pMaterial->textureFilenames[j]) > 0)
			{
				std::string path = a_pScene->GetPath();
				path += pMaterial->textureFilenames[j];
				pMaterial->textureIDs[j] = LoadTexture(path.c_str(),GL_BGRA);

				printf("Loading texture %i: %s - ID: %i\n",j, path.c_str(),pMaterial->textureIDs[j]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void GSLab05::DestroyFBXSceneResources(FBXScene* a_pScene)
{
	// remove meshes
	for ( unsigned int i = 0 ; i < a_pScene->GetMeshCount() ; ++i )
	{
		FBXMeshNode* pMesh = a_pScene->GetMeshByIndex(i);

		RenderObject* ro = (RenderObject*)pMesh->m_userData;

		glDeleteVertexArrays(1, &ro->VAO);
		glDeleteBuffers(1, &ro->VBO);
		glDeleteBuffers(1, &ro->IBO);
	}

	// remove textures
	for ( unsigned int i = 0 ; i < a_pScene->GetMaterialCount() ; ++i )
	{
		FBXMaterial* pMaterial = a_pScene->GetMaterialByIndex(i);

		for ( int j = 0 ; j < FBXMaterial::TextureTypes_Count ; ++j )
		{
			if (pMaterial->textureIDs[j] != 0)
				glDeleteTextures(1,&pMaterial->textureIDs[j]);
		}
	}
}