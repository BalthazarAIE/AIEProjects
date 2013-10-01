#ifndef _CRENDERMANAGER_H_
#define _CRENDERMANAGER_H_

#include <vector>
#include <map>
#include "MeshNode.h"
#include <GL\glew.h>
#include "ParticleManager.h"
#include "QuadMesh.h"
#include "Camera.h"
#include "FBXLoader.h"

//Render data attached to each FBXMeshNode's m_userData pointer
struct RenderObject
{
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
};

class CRenderManager
{
public:
							CRenderManager();
							~CRenderManager();

	void					Init();

	void					LoadBasicShader();
	void					LoadWaterShader();
	void					LoadLab02Shader();
	void					LoadLab03Shader();
	void					LoadLab04Shader();
	void					LoadLab09Shader();
	void					LoadLab07Shader();
	void					LoadLab08Shader();
	void					LoadFBXShader();
	void					LoadParticle2DShader();
	void					LoadParticle3DShader();
	void					LoadRefractionShader();
	void					LoadGaussianShader();
	void					LoadFullscreenQuadShader();

	void					InitFrameBuffers();

	void					AddNode(	int a_iStateID, MeshNode* a_poNode );
	void					RemoveNode( int a_iStateID, MeshNode* a_poNode );
	void					AddParticleManager(		int a_iStateID, ParticleManager* a_poParticleManager );
	void					RemoveParticleManager(	int a_iStateID, ParticleManager* a_poParticleManager );
	void					Update( float a_fDeltaTime );
	void					SetActiveCamera( Camera* a_poCamera ) { m_poActiveCamera = a_poCamera; }
	void					SetShader( GLuint a_uiShaderID );
	GLuint					GetShader() { return m_iCurrentShaderID; }
	void					SetFBXScene(FBXScene &a_oScene) { m_oScene = a_oScene; }
	void					Draw( int a_eStateID, AIE::mat4 a_cameraMatrix );
	void					DrawLab01( AIE::mat4 a_cameraMatrix );
	void					DrawLab02( AIE::mat4 a_cameraMatrix );
	void					DrawLab03( AIE::mat4 a_cameraMatrix );
	void					DrawLab04( AIE::mat4 a_cameraMatrix );
	void					DrawLab05( AIE::mat4 a_cameraMatrix );
	void					DrawLab07( AIE::mat4 a_cameraMatrix );
	void					DrawLab08( AIE::mat4 a_cameraMatrix );
	void					DrawLab09( AIE::mat4 a_cameraMatrix );
	void					DrawParticles( AIE::mat4 a_cameraMatrix );

private:
	std::vector<MeshNode*>	m_apoLab01NodesToRender;
	std::vector<MeshNode*>	m_apoLab02NodesToRender;
	std::vector<MeshNode*>	m_apoLab03NodesToRender;
	std::vector<MeshNode*>	m_apoLab04NodesToRender;
	std::vector<MeshNode*>	m_apoLab05NodesToRender;
	std::vector<MeshNode*>	m_apoLab07NodesToRender;
	std::vector<MeshNode*>	m_apoLab08NodesToRender;
	std::vector<MeshNode*>	m_apoLab09NodesToRender;
	std::map<int, ParticleManager*> m_ParticleManagers;

	QuadMesh*				m_poFullScreenQuad0;
	QuadMesh*				m_poFullScreenQuad1;
	Camera*					m_poActiveCamera;

	mat4					m_projectionMatrix;
	mat4					m_viewMatrix;
	mat4					m_modelMatrix;
	mat4					m_cameraMatrix;

	GLuint					m_FBO0, m_FBT0, m_FBD0;
	GLuint					m_FBO1, m_FBT1, m_FBD1;

	GLuint					m_iCurrentShaderID;
	GLuint					m_iBasicShaderID;
	GLuint					m_iWaterShaderID;
	GLuint					m_iLab02ShaderID;
	GLuint					m_iLab03ShaderID;
	GLuint					m_iLab04ShaderID;
	GLuint					m_iLab07ShaderID;
	GLuint					m_iLab08ShaderID;
	GLuint					m_iLab09ShaderID;
	GLuint					m_iFBXShaderID;
	GLuint					m_iParticle3DShaderID;
	GLuint					m_iParticle2DShaderID;
	GLuint					m_iRefractionShaderID;
	GLuint					m_iGaussianShaderID;
	GLuint					m_iFullscreenQuadShaderID;
	GLuint					m_iProjectionID;
	GLuint					m_iViewID;
	GLuint					m_iModelID;		
	GLuint					m_iTimeID;
	GLuint					m_iColourID;

	GLuint					m_iFBProjectionID;
	GLuint					m_iFBViewID;
	GLuint					m_iFBModelID;

	FBXScene				m_oScene;

	float					m_fTimer;
	AIE::vec4				m_vColour;
	int						m_iCurrentStateID;

	GLuint					m_iWaterBumpMapID;

};

#endif