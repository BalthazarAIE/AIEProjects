#include "GSLab09.h"
#include "CApplication.h"
#include "CRenderManager.h"

GSLab09::GSLab09(EGameState a_eStateID, CApplication* a_pApp)
	: IBaseGameState(a_pApp)
{
	m_eStateID = a_eStateID;
	m_fTimer = 0.f;

	// load FBX scene
	m_oScene.LoadAIE("scenes/Marv/Marv.aie");
	InitFBXSceneResources(&m_oScene);

	m_poTitle = new PlaneNode( 5.f, 5.f, 2, 2, AIE::vec4(0.f,0.f,0.f,1.f) );
	m_poTitle->SetTexture( LoadTexture("./images/lab09.png") );
	Quaternion m_qPlaneRot;
	m_qPlaneRot.CreateRotation(-PI/2, AIE::vec4(1.f, 0.f, 0.f, 0.f) );
	m_poTitle->RotateNode( m_qPlaneRot );
	m_poTitle->TranslateNode( AIE::vec4(5.f, 100.f, -580.f, 0.f) );
	m_poTitle->UpdateBuffers();

	m_pApp->GetRenderManager()->AddNode( m_eStateID, m_poTitle );
}

GSLab09::~GSLab09()
{
	DestroyFBXSceneResources(&m_oScene);
	m_oScene.Unload();

	delete m_poTitle;
	m_poTitle = nullptr;
}

void GSLab09::Load()
{
	m_poCamera = new Camera( AIE::vec4(0.f,100.f,-600.f,1.f), AIE::vec4(0.f,0.f,1.f,1.f), AIE::vec4(0.f,1.f,0.f,0.f) );
	m_pApp->GetRenderManager()->SetActiveCamera( m_poCamera );
	m_pApp->GetRenderManager()->SetFBXScene( m_oScene );

	printf( "\n\n------------------------------------------------\n"
			"Lab 09 - Animation - Skinning\n\n"

			"Relevant code can be found in:\n\n"

			"'lab09' shaders\n"
			"GSLab09.h & .cpp\n"
			"DrawLab09() function in CRenderManager.cpp\n"
			"------------------------------------------------\n" );
}

void GSLab09::Unload()
{
	delete m_poCamera;
	m_poCamera = nullptr;
}

void GSLab09::Update(float a_fDeltaTime)
{
	m_fTimer += a_fDeltaTime;
	m_poCamera->Update( a_fDeltaTime );

	FBXAnimation* anim	= m_oScene.GetAnimationByIndex( 8 );
	m_oScene.GetSkeletonByIndex(0)->Evaluate( anim, m_fTimer );
}	 

void GSLab09::Draw()
{
	m_pApp->GetRenderManager()->Draw( m_eStateID, m_poCamera->GetViewMatrix() );
}

//////////////////////////////////////////////////////////////////////////
void GSLab09::InitFBXSceneResources(FBXScene* a_pScene)
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
void GSLab09::DestroyFBXSceneResources(FBXScene* a_pScene)
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