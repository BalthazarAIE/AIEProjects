#include "CRenderManager.h"

CRenderManager::CRenderManager()
{
	m_iCurrentStateID = 0;

	m_fTimer = 0.f;
	m_vColour = AIE::vec4( 0.02f, 0.02f, 0.02f, 1.0f );

	m_iWaterBumpMapID = LoadTexture( "./images/water_bump_map.jpg" );
	
	Init();
}

CRenderManager::~CRenderManager()
{
	delete m_poFullScreenQuad1;
	m_poFullScreenQuad1 = nullptr;
	delete m_poFullScreenQuad0;
	m_poFullScreenQuad0 = nullptr;

	glDeleteTextures( 1, &m_iWaterBumpMapID );

	glDeleteShader( m_iBasicShaderID );
	glDeleteShader( m_iWaterShaderID );
	glDeleteShader( m_iLab02ShaderID );
	glDeleteShader( m_iLab03ShaderID );
	glDeleteShader( m_iLab04ShaderID );
	glDeleteShader( m_iLab07ShaderID );
	glDeleteShader( m_iLab08ShaderID );
	glDeleteShader( m_iLab09ShaderID );
	glDeleteShader( m_iFBXShaderID );
	glDeleteShader( m_iParticle2DShaderID );
	glDeleteShader( m_iParticle3DShaderID );
	glDeleteShader( m_iRefractionShaderID );
	glDeleteShader( m_iGaussianShaderID );
	glDeleteShader( m_iFullscreenQuadShaderID );

}

void CRenderManager::Init()
{
	//Setup matrices
	m_cameraMatrix.SetFrame(	vec4( 0.f, 0.f, -50.f,	1.f ), 
								vec4( 0.f, 0.f, 0.5f,	1.f ), 
								vec4( 0.f, 1.f,	0.f,	0.f )	);
	m_projectionMatrix.Perspective(	PI/6.f, 1280.f/720.0f, 0.1f, 1500.f);
	m_viewMatrix	= m_cameraMatrix.ToViewMatrix();
	m_modelMatrix	= mat4(	1.f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f	);

	///////////////////////////////////////////
	//	LOAD SHADERS
	///////////////////////////////////////////

	LoadBasicShader();
	LoadWaterShader();
	LoadLab02Shader();
	LoadLab03Shader();
	LoadLab04Shader();
	LoadLab07Shader();
	LoadLab08Shader();
	LoadLab09Shader();
	LoadFBXShader();
	LoadParticle2DShader();
	LoadParticle3DShader();
	LoadRefractionShader();
	LoadGaussianShader();
	LoadFullscreenQuadShader();

	InitFrameBuffers();

	//Set clear colour
	glClearColor(0.25f,0.25f,0.25f,1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_poFullScreenQuad0 = new QuadMesh();
	m_poFullScreenQuad0->Init();
	m_poFullScreenQuad1 = new QuadMesh();
	m_poFullScreenQuad1->Init();
}

void CRenderManager::LoadBasicShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iBasicShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/basic_vertex.glsl",
												"./shaders/basic_fragment.glsl",
												"./shaders/basic_geometry.glsl",
												"./shaders/basic_tess_control.glsl",
												"./shaders/basic_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iBasicShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iBasicShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iBasicShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iBasicShaderID,	"Time"			);

	GLuint texUniformID = glGetUniformLocation( m_iBasicShaderID, "diffuseTexture" );
	glUniform1i(texUniformID,0);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
}

void CRenderManager::LoadWaterShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iWaterShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab01_water_vertex.glsl",
												"./shaders/lab01_water_fragment.glsl",
												"./shaders/lab01_water_geometry.glsl",
												"./shaders/lab01_water_tess_control.glsl",
												"./shaders/lab01_water_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iWaterShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iWaterShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iWaterShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iWaterShaderID,	"Time"			);

	GLuint texUniformID = glGetUniformLocation( m_iWaterShaderID, "diffuseTexture" );
	glUniform1i(texUniformID,0);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
}

void CRenderManager::LoadLab02Shader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iLab02ShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab02_vertex.glsl",
												"./shaders/lab02_fragment.glsl",
												"./shaders/lab02_geometry.glsl",
												"./shaders/lab02_tess_control.glsl",
												"./shaders/lab02_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iLab02ShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iLab02ShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iLab02ShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iLab02ShaderID,	"Time"			);
	m_iColourID			= glGetUniformLocation( m_iLab02ShaderID,	"Colour"		);

	GLuint texUniformID = glGetUniformLocation( m_iLab02ShaderID, "diffuseTexture" );
	glUniform1i(texUniformID,0);
	GLuint texUniformID2 = glGetUniformLocation( m_iLab02ShaderID, "secondaryTexture" );
	glUniform1i(texUniformID,1);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
	glUniform4fv( m_iColourID, 1, m_vColour );
}

void CRenderManager::LoadLab03Shader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iLab03ShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab03_vertex.glsl",
												"./shaders/lab03_fragment.glsl",
												"./shaders/lab03_geometry.glsl",
												"./shaders/lab03_tess_control.glsl",
												"./shaders/lab03_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iLab03ShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iLab03ShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iLab03ShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iLab03ShaderID,	"Time"			);
	m_iColourID			= glGetUniformLocation( m_iLab03ShaderID,	"Colour"		);

	GLuint texUniformID0 = glGetUniformLocation( m_iLab03ShaderID, "diffuseTexture" );
	glUniform1i(texUniformID0,0);
	GLuint texUniformID1 = glGetUniformLocation( m_iLab03ShaderID, "secondaryTexture" );
	glUniform1i(texUniformID1,1);
	GLuint texUniformID2 = glGetUniformLocation( m_iLab03ShaderID, "displacementTexture" );
	glUniform1i(texUniformID2,2);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
	glUniform4fv( m_iColourID, 1, m_vColour );
}

void CRenderManager::LoadLab04Shader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iLab04ShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab04_vertex.glsl",
												"./shaders/lab04_fragment.glsl",
												"./shaders/lab04_geometry.glsl",
												"./shaders/lab04_tess_control.glsl",
												"./shaders/lab04_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iLab04ShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iLab04ShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iLab04ShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iLab04ShaderID,	"Time"			);
	m_iColourID			= glGetUniformLocation( m_iLab04ShaderID,	"Colour"		);

	GLuint texUniformID0 = glGetUniformLocation( m_iLab04ShaderID, "diffuseTexture" );
	glUniform1i(texUniformID0,0);
	GLuint texUniformID1 = glGetUniformLocation( m_iLab04ShaderID, "secondaryTexture" );
	glUniform1i(texUniformID1,1);
	GLuint texUniformID2 = glGetUniformLocation( m_iLab04ShaderID, "displacementTexture" );
	glUniform1i(texUniformID2,2);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
	glUniform4fv( m_iColourID, 1, m_vColour );
}

void CRenderManager::LoadLab07Shader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iLab07ShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab07_vertex.glsl",
												"./shaders/lab07_fragment.glsl",
												"./shaders/lab07_geometry.glsl",
												"./shaders/lab07_tess_control.glsl",
												"./shaders/lab07_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iLab07ShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iLab07ShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iLab07ShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iLab07ShaderID,	"Time"			);

	GLuint texUniformID = glGetUniformLocation( m_iLab07ShaderID, "diffuseTexture" );
	glUniform1i(texUniformID,0);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
}

void CRenderManager::LoadLab08Shader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iLab08ShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/lab08_vertex.glsl",
												"./shaders/lab08_fragment.glsl",
												"./shaders/lab08_geometry.glsl",
												"./shaders/lab08_tess_control.glsl",
												"./shaders/lab08_tess_eval.glsl");

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iLab08ShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iLab08ShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iLab08ShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iLab08ShaderID,	"Time"			);

	GLuint texUniformID = glGetUniformLocation( m_iLab08ShaderID, "diffuseTexture" );
	glUniform1i(texUniformID,0);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
}

void CRenderManager::LoadLab09Shader()
{
	
	const char* aszInputs[] = {	"Position",
								"Normal",
								"Tangent",
								"BiNormal",
								"Indices",
								"Weights",
								"UV" };

	const char* aszOutputs[] = { "outColour" };

	m_iLab09ShaderID			= LoadShader(	7, aszInputs, 0, aszOutputs,
												"./shaders/lab09_vertex.glsl",
												"./shaders/lab09_fragment.glsl" );
}

void CRenderManager::LoadFBXShader()
{

	const char* aszInputs[] = {	"Position",
								"Normal",
								"Tangent",
								"BiNormal",
								"Indices",
								"Weights",
								"UV" };

	const char* aszOutputs[] = { "outColour" };

	// load shader
	m_iFBXShaderID = LoadShader( 7, aszInputs, 1, aszOutputs,
		"./shaders/normalmap_vertex.glsl",
		"./shaders/normalmap_pixel.glsl");
}

void CRenderManager::LoadParticle2DShader()
{
	const char* aszStandardInputs[]		= { "Position",	"Size", "Alpha" };
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iParticle2DShaderID			= LoadShader(	3, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/particle_2d_vertex.glsl",
												"./shaders/particle_2d_fragment.glsl",
												"./shaders/particle_2d_geometry.glsl" );

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iParticle2DShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iParticle2DShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iParticle2DShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iParticle2DShaderID,	"Time"			);
	m_iColourID			= glGetUniformLocation( m_iParticle2DShaderID,	"Colour"		);

	GLuint texUniformID0 = glGetUniformLocation( m_iParticle2DShaderID, "diffuseTexture" );
	glUniform1i(texUniformID0,0);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
	glUniform4fv( m_iColourID, 1, m_vColour );
}

void CRenderManager::LoadParticle3DShader()
{
	const char* aszStandardInputs[]		= { "Position",	"Size", "Alpha", "Colour" };
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iParticle3DShaderID			= LoadShader(	4, aszStandardInputs, 0, aszStandardOutputs,
												"./shaders/particle_3d_vertex.glsl",
												"./shaders/particle_3d_fragment.glsl",
												"./shaders/particle_3d_geometry.glsl" );

	//Set matrix uniforms in the shader
	m_iProjectionID		= glGetUniformLocation( m_iParticle3DShaderID,	"Projection"	);
	m_iViewID			= glGetUniformLocation( m_iParticle3DShaderID,	"View"			);
	m_iModelID			= glGetUniformLocation( m_iParticle3DShaderID,	"Model"			);
	m_iTimeID			= glGetUniformLocation( m_iParticle3DShaderID,	"Time"			);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
}

void CRenderManager::LoadRefractionShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iRefractionShaderID			= LoadShader(	2, aszStandardInputs, 1, aszStandardOutputs,
												"./shaders/refraction_vertex.glsl",
												"./shaders/refraction_fragment.glsl",
												"./shaders/refraction_geometry.glsl",
												"./shaders/refraction_tess_control.glsl",
												"./shaders/refraction_tess_eval.glsl");
}

void CRenderManager::LoadGaussianShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iGaussianShaderID			= LoadShader(	2, aszStandardInputs, 1, aszStandardOutputs,
												"./shaders/gaussian_vertex.glsl",
												"./shaders/gaussian_fragment.glsl");
}

void CRenderManager::LoadFullscreenQuadShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iFullscreenQuadShaderID			= LoadShader(	2, aszStandardInputs, 1, aszStandardOutputs,
												"./shaders/fullscreen_quad_vertex.glsl",
												"./shaders/fullscreen_quad_fragment.glsl");
}

void CRenderManager::InitFrameBuffers()
{
	///////////////////////////////////////////
	//	FIRST RENDER BUFFER INITIALISATION
	///////////////////////////////////////////

	// create render buffer to hold frame buffer's depth info
	glGenRenderbuffers			( 1, &m_FBD0 );
	glBindRenderbuffer			( GL_RENDERBUFFER, m_FBD0 );
	glRenderbufferStorage		( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720 );
	glFramebufferRenderbuffer	( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_FBD0 );
	glBindRenderbuffer			( GL_RENDERBUFFER, 0 );

	// create Texture object to hold Frame Buffer's rendered data (output from pixel shader)
	glGenTextures	( 1, &m_FBT0 );
	glBindTexture	( GL_TEXTURE_2D, m_FBT0 );
	glTexImage2D	( GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameterf	( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf	( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri	( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri	( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glBindTexture	( GL_TEXTURE_2D, 0 );

	// create Frame Buffer Object and attach the render buffer and texture object
	glGenFramebuffers			( 1, &m_FBO0 );
	glBindFramebuffer			( GL_FRAMEBUFFER, m_FBO0 );
	glFramebufferTexture2D		( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBT0, 0 );
	glFramebufferRenderbuffer	( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_FBD0 );

	if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
		printf( "Error creating frame buffer!\n" );

	///////////////////////////////////////////
	//	SECOND RENDER BUFFER INITIALISATION
	///////////////////////////////////////////

	// create render buffer to hold frame buffer's depth info
	glGenRenderbuffers			( 1, &m_FBD1 );
	glBindRenderbuffer			( GL_RENDERBUFFER, m_FBD1 );
	glRenderbufferStorage		( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720 );
	glFramebufferRenderbuffer	( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_FBD1 );
	glBindRenderbuffer			( GL_RENDERBUFFER, 0 );

	// create Texture object to hold Frame Buffer's rendered data (output from pixel shader)
	glGenTextures	( 1, &m_FBT1 );
	glBindTexture	( GL_TEXTURE_2D, m_FBT1 );
	glTexImage2D	( GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameterf	( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf	( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri	( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri	( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glBindTexture	( GL_TEXTURE_2D, 0 );

	// create Frame Buffer Object and attach the render buffer and texture object
	glGenFramebuffers			( 1, &m_FBO1 );
	glBindFramebuffer			( GL_FRAMEBUFFER, m_FBO1 );
	glFramebufferTexture2D		( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBT1, 0 );
	glFramebufferRenderbuffer	( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_FBD1 );

	if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
		printf( "Error creating frame buffer!\n" );

	// reset back to using the default Frame Buffer, aka the Back Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void CRenderManager::AddNode( int a_iStateID, MeshNode* a_poNode )
{	 
	switch( a_iStateID )
	{
	case 0:
		m_apoLab01NodesToRender.push_back( a_poNode );
		break;
	case 1:
		m_apoLab02NodesToRender.push_back( a_poNode );
		break;
	case 2:
		m_apoLab03NodesToRender.push_back( a_poNode );
		break;
	case 3:
		m_apoLab04NodesToRender.push_back( a_poNode );
		break;
	case 4:
		m_apoLab05NodesToRender.push_back( a_poNode );
		break;
	case 5:
		m_apoLab07NodesToRender.push_back( a_poNode );
		break;
	case 6:
		m_apoLab08NodesToRender.push_back( a_poNode );
		break;
	case 7:
		m_apoLab09NodesToRender.push_back( a_poNode );
		break;
	default:
		return;
	};
}
	 
void CRenderManager::RemoveNode( int a_iStateID, MeshNode* a_poNode )
{	 
	std::vector<MeshNode*>* nodes;

	switch( a_iStateID )
	{
	case 0:
		nodes = &m_apoLab01NodesToRender;
		break;
	case 1:
		nodes = &m_apoLab02NodesToRender;
		break;
	case 2:
		nodes = &m_apoLab03NodesToRender;
		break;
	case 3:
		nodes = &m_apoLab04NodesToRender;
		break;
	case 4:
		nodes = &m_apoLab05NodesToRender;
		break;
	case 5:
		nodes = &m_apoLab07NodesToRender;
		break;
	case 6:
		nodes = &m_apoLab08NodesToRender;
		break;
	case 7:
		nodes = &m_apoLab09NodesToRender;
		break;
	};

	std::vector<MeshNode*>::iterator iter;
	iter = nodes->begin();

	while( iter != nodes->end() )
	{
		if( (*iter) == a_poNode )
		{
			nodes->erase( iter );
			break;
		}
		++iter;
	}
}

void CRenderManager::AddParticleManager( int a_iStateID, ParticleManager* a_poParticleManager )
{
	m_ParticleManagers[ a_iStateID ] = a_poParticleManager;
}

void CRenderManager::RemoveParticleManager( int a_iStateID, ParticleManager* a_poParticleManager )
{
	m_ParticleManagers.erase( a_iStateID );
}
	 
void CRenderManager::Update( float a_fDeltaTime )
{
	m_fTimer += a_fDeltaTime;
}	 

void CRenderManager::SetShader( GLuint a_uiShaderID )
{
	if( m_iCurrentShaderID != a_uiShaderID )
	{
		m_iCurrentShaderID = a_uiShaderID;
		// set active shader
		glUseProgram(a_uiShaderID);
	}

	// convert camera's world matrix to a view matrix
	m_viewMatrix = m_poActiveCamera->GetViewMatrix().ToViewMatrix();

	// set current transforms in the shader
	m_iProjectionID = glGetUniformLocation( a_uiShaderID, "Projection"	);
	m_iViewID		= glGetUniformLocation( a_uiShaderID, "View"		);
	m_iModelID		= glGetUniformLocation( a_uiShaderID, "Model"		);
	m_iTimeID		= glGetUniformLocation( a_uiShaderID, "Time"		);

	glUniformMatrix4fv( m_iProjectionID,	1, false, m_projectionMatrix	);
	glUniformMatrix4fv( m_iViewID,			1, false, m_viewMatrix			);
	glUniformMatrix4fv( m_iModelID,			1, false, m_modelMatrix			);
	glUniform1f( m_iTimeID, m_fTimer );
}
	 
void CRenderManager::Draw( int a_iStateID, AIE::mat4 a_cameraMatrix )
{
	// clear the backbuffer to our clear colour and clear the depth
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_iCurrentStateID = a_iStateID;

	switch( a_iStateID )
	{
	case 0:
		DrawLab01( a_cameraMatrix );
		break;
	case 1:
		DrawLab02( a_cameraMatrix );
		break;
	case 2:
		DrawLab03( a_cameraMatrix );
		break;
	case 3:
		DrawLab04( a_cameraMatrix );
		break;
	case 4:
		DrawLab05( a_cameraMatrix );
		break;
	case 5:
		DrawLab07( a_cameraMatrix );
		break;
	case 6:
		DrawLab08( a_cameraMatrix );
		break;
	case 7:
		DrawLab09( a_cameraMatrix );
		break;
	default:
		return;
	};
}

void CRenderManager::DrawLab01( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iBasicShaderID);

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab01NodesToRender.begin();

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	int i = 0;
	while( iter != m_apoLab01NodesToRender.end() )
	{
		if( i == 4 )		SetShader(m_iWaterShaderID);
		(*iter)->Draw();
		++iter;
		++i;
	}

	auto pIter = m_ParticleManagers.find( m_iCurrentStateID );
	if( pIter != m_ParticleManagers.end() )
		(*pIter).second->Draw( m_projectionMatrix, m_viewMatrix, m_modelMatrix, a_cameraMatrix );
}

void CRenderManager::DrawLab02( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iLab02ShaderID);
	AIE::vec4 camPos = a_cameraMatrix.row3;

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab02NodesToRender.begin();

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	int i = 0;
	while( iter != m_apoLab02NodesToRender.end() )
	{
		//if( i == 4 )
			//SetShader(m_iBasicShaderID);
		GLuint texUniformID = glGetUniformLocation( m_iLab02ShaderID, "diffuseTexture" );
		glUniform1i(texUniformID,0);
		GLuint texUniformID2 = glGetUniformLocation( m_iLab02ShaderID, "secondaryTexture" );
		glUniform1i(texUniformID2,1);
		m_iColourID		= glGetUniformLocation( m_iLab02ShaderID,	"Colour"		);
		glUniform4fv( m_iColourID, 1, m_vColour );

		float dist = AIE::vec4( camPos - (*iter)->GetWorldTransform().row3 ).Magnitude();
		GLuint distUniformID = glGetUniformLocation( m_iLab02ShaderID, "Distance" );
		glUniform1f( distUniformID,	dist);

		(*iter)->Draw();
		++iter;
		++i;
	}

	auto pIter = m_ParticleManagers.find( m_iCurrentStateID );
	if( pIter != m_ParticleManagers.end() )
		(*pIter).second->Draw( m_projectionMatrix, m_viewMatrix, m_modelMatrix, a_cameraMatrix );
}

void CRenderManager::DrawLab03( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iBasicShaderID);
	AIE::vec4 camPos = a_cameraMatrix.row3;

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab03NodesToRender.begin();

	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	int i = 0;
	while( iter != m_apoLab03NodesToRender.end() )
	{
		if( i > 1 )
			SetShader(m_iLab03ShaderID);
		GLuint texUniformID = glGetUniformLocation( m_iLab03ShaderID, "diffuseTexture" );
		glUniform1i(texUniformID,0);
		GLuint texUniformID2 = glGetUniformLocation( m_iLab03ShaderID, "secondaryTexture" );
		glUniform1i(texUniformID2,1);
		m_iColourID		= glGetUniformLocation( m_iLab03ShaderID,	"Colour"		);
		glUniform4fv( m_iColourID, 1, m_vColour );

		float dist = AIE::vec4( camPos - (*iter)->GetWorldTransform().row3 ).Magnitude();
		GLuint distUniformID = glGetUniformLocation( m_iLab03ShaderID, "Distance" );
		glUniform1f( distUniformID,	dist);
		GLuint camPosUniformID = glGetUniformLocation( m_iLab03ShaderID, "CameraPos" );
		glUniform4fv( camPosUniformID, 1, camPos);

		(*iter)->Draw();
		++iter;
		++i;
	}

	auto pIter = m_ParticleManagers.find( m_iCurrentStateID );
	if( pIter != m_ParticleManagers.end() )
	{
		std::vector<ParticleSystem*> systems = (*pIter).second->GetActiveEmitters();
		auto sIter = systems.begin();
		while ( sIter != systems.end() )
		{
			if ( (*sIter)->Is3D() )
			{
				SetShader(m_iParticle3DShaderID);
				GLuint ProjectionID = glGetUniformLocation(	m_iParticle3DShaderID, "Projection" );
				glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
				GLuint ViewID = glGetUniformLocation(	m_iParticle3DShaderID, "View" );
				glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
				GLuint ModelID = glGetUniformLocation(	m_iParticle3DShaderID, "Model" );
				glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );
				GLuint CameraPosID = glGetUniformLocation( m_iParticle3DShaderID,	"CameraMat"	);
				glUniformMatrix4fv( CameraPosID, 1, false, a_cameraMatrix	);
			}
			else
			{
				SetShader(m_iParticle2DShaderID);
				GLuint texUniformID = glGetUniformLocation( m_iParticle2DShaderID, "diffuseTexture" );
				glUniform1i(texUniformID,0);
				GLuint ProjectionID = glGetUniformLocation(	m_iParticle2DShaderID, "Projection" );
				glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
				GLuint ViewID = glGetUniformLocation(	m_iParticle2DShaderID, "View" );
				glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
				GLuint ModelID = glGetUniformLocation(	m_iParticle2DShaderID, "Model" );
				glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );
				GLuint CameraPosID = glGetUniformLocation( m_iParticle2DShaderID,	"CameraMat"	);
				glUniformMatrix4fv( CameraPosID, 1, false, a_cameraMatrix	);
			}

			(*sIter)->Draw(  m_projectionMatrix, m_viewMatrix, m_modelMatrix, a_cameraMatrix );

			++sIter;
		}
	}
}

void CRenderManager::DrawLab04( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iLab04ShaderID);
	AIE::vec4 camPos = a_cameraMatrix.row3;

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab04NodesToRender.begin();

	glEnable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable(GL_CULL_FACE);

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	int i = 0;
	while( iter != m_apoLab04NodesToRender.end() )
	{
		if( i > 0 )
		{
			SetShader(m_iBasicShaderID);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		GLuint texUniformID0 = glGetUniformLocation( m_iLab04ShaderID, "diffuseTexture" );
		glUniform1i(texUniformID0,0);
		GLuint texUniformID1 = glGetUniformLocation( m_iLab04ShaderID, "secondaryTexture" );
		glUniform1i(texUniformID1,1);
		GLuint texUniformID2 = glGetUniformLocation( m_iLab04ShaderID, "displacementTexture" );
		glUniform1i(texUniformID2,2);
		m_iColourID		= glGetUniformLocation( m_iLab04ShaderID,	"Colour"		);
		glUniform4fv( m_iColourID, 1, m_vColour );

		GLuint camPosUniformID = glGetUniformLocation( m_iLab04ShaderID, "CameraPos" );
		glUniform4fv( camPosUniformID, 1, camPos);

		(*iter)->Draw();
		++iter;
		++i;
	}

	auto pIter = m_ParticleManagers.find( m_iCurrentStateID );
	if( pIter != m_ParticleManagers.end() )
		(*pIter).second->Draw( m_projectionMatrix, m_viewMatrix, m_modelMatrix, a_cameraMatrix );
}

void CRenderManager::DrawLab05( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iBasicShaderID);

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab05NodesToRender.begin();

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	while( iter != m_apoLab05NodesToRender.end() )
	{
		(*iter)->Draw();
		++iter;
	}

	SetShader(m_iFBXShaderID);

	GLuint ProjectionID = glGetUniformLocation(	m_iFBXShaderID, "Projection" );
	glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
	GLuint ViewID = glGetUniformLocation(	m_iFBXShaderID, "View" );
	glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
	GLuint ModelID = glGetUniformLocation(	m_iFBXShaderID, "Model" );
	glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );

	AIE::vec4 camPos = a_cameraMatrix.row3;
	GLuint camPosUniformID = glGetUniformLocation( m_iFBXShaderID, "CamPos" );
	glUniform4fv( camPosUniformID, 1, camPos);

	AIE::vec4 materialDiffuseCol = AIE::vec4( 1.f, 0.9f, 0.03f, 1.f );
	GLuint MaterialID = glGetUniformLocation( m_iFBXShaderID,"materialDiffuse" );
	glUniform4fv( MaterialID, 1, materialDiffuseCol);
	AIE::vec4 ambientCol = AIE::vec4( 0.1f, 0.1f, 0.1f, 1.f );
	GLuint AmbientID = glGetUniformLocation( m_iFBXShaderID,"ambientColour" );
	glUniform4fv( AmbientID, 1, ambientCol);

	GLuint diffuseTextureID = glGetUniformLocation( m_iFBXShaderID, "diffuseTexture" );
	glUniform1i( diffuseTextureID, 0 );
	GLuint normalTextureID = glGetUniformLocation( m_iFBXShaderID, "normalTexture" );
	glUniform1i( normalTextureID, 1 );
	GLuint specularTextureID = glGetUniformLocation( m_iFBXShaderID, "specularTexture" );
	glUniform1i( specularTextureID, 2 );

	//Directional Light Uniforms
	AIE::vec4 lightDirection(0,1,-1,0);
	AIE::vec4 lightColour(1,1,1,0);

	GLuint dirLightDirID = glGetUniformLocation( m_iFBXShaderID, "dirLightDir" );
	glUniform4fv( dirLightDirID, 1, lightDirection);
	GLuint dirLightColID = glGetUniformLocation( m_iFBXShaderID, "dirLightCol" );
	glUniform4fv( dirLightColID, 1, lightColour);

	//Point Light Uniforms
	AIE::vec4 pointLightPos( 0.f, 2.f, -20.f, 1.f );
	AIE::vec4 pointLightCol( 1.f, 0.f, 0.f, 1.f );

	GLuint pointLightPosID = glGetUniformLocation( m_iFBXShaderID, "pointLightPos" );
	glUniform4fv( pointLightPosID, 1, pointLightPos);
	GLuint pointLightColID = glGetUniformLocation( m_iFBXShaderID, "pointLightCol" );
	glUniform4fv( pointLightColID, 1, pointLightCol);

	//Spot Light Uniforms
	float y = 3.0f + sin( m_fTimer );
	AIE::vec4 spotLightPos( 0.f, y, -2.f, 1.f );
	AIE::vec4 spotLightDir( 0.f, 0.f, 1.f, 1.f );
	AIE::vec4 spotLightCol( 1.f, 1.f, 1.f, 1.f );

	GLuint spotLightPosID = glGetUniformLocation( m_iFBXShaderID, "spotLightPos" );
	glUniform4fv( spotLightPosID, 1, spotLightPos);
	GLuint spotLightDirID = glGetUniformLocation( m_iFBXShaderID, "spotLightDir" );
	glUniform4fv( spotLightDirID, 1, spotLightDir);
	GLuint spotLightColID = glGetUniformLocation( m_iFBXShaderID, "spotLightCol" );
	glUniform4fv( spotLightColID, 1, spotLightCol);

	GLuint timeID = glGetUniformLocation( m_iFBXShaderID, "time" );
	glUniform1f( timeID, m_fTimer );

	for(unsigned int i = 0; i < m_oScene.GetMeshCount(); ++i)
	{
		FBXMeshNode* pMesh = m_oScene.GetMeshByIndex(i);

		// get the render object IDs stored in the mesh's user data
		RenderObject* ro = (RenderObject*)pMesh->m_userData;

		// set the mesh's material in the shader
		glUniform4fv(MaterialID, 1, &(pMesh->m_material->diffuse.x));

		// set the mesh's textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::DiffuseTexture] );
		glActiveTexture(GL_TEXTURE1);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::NormalTexture] );
		glActiveTexture(GL_TEXTURE2);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::SpecularTexture] );

		// apply the meshes global transform
		glUniformMatrix4fv( ModelID, 1, false, pMesh->m_globalTransform );

		// bind buffers and draw
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, pMesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void CRenderManager::DrawLab07( AIE::mat4 a_cameraMatrix )
{
	///////////////////////////////////////////
	////////BIND FIRST FRAME BUFFER////////////
	///////////////////////////////////////////

	//Set to render to the Frame Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, m_FBO0 );

	//Set the viewport to the size of the Frame Buffer
	glViewport( 0, 0, 1280, 720 );

	//Clear the Frame Buffer's depth and colour targets
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//////////////////////////////////////////////
	////////DRAW TO FIRST FRAME BUFFER////////////
	//////////////////////////////////////////////
	SetShader(m_iBasicShaderID);

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	int i = 0;
	auto iter = m_apoLab07NodesToRender.begin();
	while( iter != m_apoLab07NodesToRender.end() )
	{
		if( i > 1 )
			break;
		if( i == 1 )
			SetShader(m_iLab07ShaderID);
		GLuint ColourID = glGetUniformLocation(	m_iLab07ShaderID, "Colour" );
		glUniform4fv( ColourID, 1, (*iter)->GetColour() );
		float passNum = 1;
		GLuint PassNumID = glGetUniformLocation( m_iLab07ShaderID, "PassNumber" );
		glUniform1fv( PassNumID, 1, &passNum );

		(*iter)->Draw();
		++iter;
		++i;
	}

	DrawParticles( a_cameraMatrix );

	////////////////////////////////////////////
	////////BIND FINAL FRAME BUFFER/////////////
	////////////////////////////////////////////

	//Set to render to the second frame Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, m_FBO1 );

	//Set the viewport to the size of the Frame Buffer
	glViewport( 0, 0, 1280, 720 );

	//Clear the Frame Buffer's depth and colour targets
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//////////////////////////////////////////////
	//////DRAW TO FINAL FRAME BUFFER/////////////
	//////////////////////////////////////////////

	SetShader(m_iBasicShaderID);

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	i = 0;
	iter = m_apoLab07NodesToRender.begin();
	while( iter != m_apoLab07NodesToRender.end() )
	{
		if( i > 1 )
			break;
		if( i == 1 )
			SetShader(m_iLab07ShaderID);
		GLuint ColourID = glGetUniformLocation(	m_iLab07ShaderID, "Colour" );
		glUniform4fv( ColourID, 1, (*iter)->GetColour() );
		(*iter)->Draw();
		++iter;
		++i;
	}

	SetShader( m_iRefractionShaderID );
	GLuint TimeID = glGetUniformLocation( m_iRefractionShaderID,	"Time"	);
	glUniform1f( TimeID, m_fTimer	);
	GLuint TextureID = glGetUniformLocation( m_iRefractionShaderID, "Texture" );
	glUniform1i( TextureID, 0 );
	GLuint SceneID = glGetUniformLocation( m_iRefractionShaderID, "SceneTexture" );
	glUniform1i( SceneID, 1 );
	GLuint BumpMapID = glGetUniformLocation( m_iRefractionShaderID, "WaterBumpMap" );
	glUniform1i( BumpMapID, 2 );

	(*iter)->SetSecondaryTexture( m_FBT0 );
	(*iter)->SetDisplacementTexture( m_iWaterBumpMapID );
	(*iter)->Draw();

	DrawParticles( a_cameraMatrix );

	SetShader(m_iBasicShaderID);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	++iter;
	(*iter)->Draw();

	////////////////////////////////////////////
	////////FIRST GAUSSIAN BLUR PASS////////////
	////////////////////////////////////////////

	//Set to render to the second frame Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, m_FBO0 );

	//Set the viewport to the size of the Frame Buffer
	glViewport( 0, 0, 1280, 720 );

	//Clear the Frame Buffer's depth and colour targets
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	////////////////////////////////////////////////
	////////DRAW TO FRAME BUFFER/////////////
	////////////////////////////////////////////////

	SetShader(m_iGaussianShaderID);
	GLuint PassNumID = glGetUniformLocation( m_iGaussianShaderID, "PassNumber" );
	glUniform1i( PassNumID, 1 );

	TextureID = glGetUniformLocation( m_iGaussianShaderID, "RenderBuffer" );
	glUniform1i( TextureID, 0 );

	m_poFullScreenQuad0->SetTexture( m_FBT1 );
	m_poFullScreenQuad0->Draw();

	////////////////////////////////////////////
	////////SECOND GAUSSIAN BLUR PASS////////////
	////////////////////////////////////////////

	//Set to render to the second frame Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, m_FBO1 );

	//Set the viewport to the size of the Frame Buffer
	glViewport( 0, 0, 1280, 720 );

	//Clear the Frame Buffer's depth and colour targets
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	////////////////////////////////////////////////
	////////DRAW TO FRAME BUFFER/////////////
	////////////////////////////////////////////////

	SetShader(m_iGaussianShaderID);
	glUniform1i( PassNumID, 2 );

	TextureID = glGetUniformLocation( m_iGaussianShaderID, "RenderBuffer" );
	glUniform1i( TextureID, 0 );

	m_poFullScreenQuad0->SetTexture( m_FBT0 );
	m_poFullScreenQuad0->Draw();

	///////////////////////////////////////
	//////////BIND BACK BUFFER/////////////
	///////////////////////////////////////

	// Set the target back to the Back Buffer (default Frame Buffer)
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	//Set the viewport to the size of the screen
	glViewport( 0, 0, 1280, 720 );

	//Clear the Back Buffer's depth and colour
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	////////////////////////////////////////
	////////DRAW TO BACK BUFFER/////////////
	////////////////////////////////////////

	SetShader( m_iFullscreenQuadShaderID );

	//TextureID = glGetUniformLocation( m_iFullscreenQuadShaderID, "SceneTexture" );
	//glUniform1i( TextureID, 0 );
	//BumpMapID = glGetUniformLocation( m_iFullscreenQuadShaderID, "SecondaryTexture" );
	//glUniform1i( BumpMapID, 1 );

	m_poFullScreenQuad0->SetTexture( m_FBT0 );
	m_poFullScreenQuad0->SetSecondaryTexture( m_FBT1 );
	m_poFullScreenQuad0->Draw();
}

void CRenderManager::DrawLab08( AIE::mat4 a_cameraMatrix )
{
	SetShader(m_iBasicShaderID);

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab08NodesToRender.begin();

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	int i = 0;
	while( iter != m_apoLab08NodesToRender.end() )
	{
		if( i > 0 )
			SetShader(m_iLab08ShaderID);
		if( i == 3 )
			SetShader(m_iBasicShaderID);
		(*iter)->Draw();
		++iter;
		++i;
	}
}

void CRenderManager::DrawLab09( AIE::mat4 a_cameraMatrix )
{
	//Drawing the FBX model
	SetShader(m_iLab09ShaderID);

	GLuint ProjectionID = glGetUniformLocation(	m_iLab09ShaderID, "Projection" );
	glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
	GLuint ViewID = glGetUniformLocation(	m_iLab09ShaderID, "View" );
	glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
	GLuint ModelID = glGetUniformLocation(	m_iLab09ShaderID, "Model" );
	glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );

	AIE::vec4 camPos = a_cameraMatrix.row3;
	GLuint camPosUniformID = glGetUniformLocation( m_iLab09ShaderID, "CamPos" );
	glUniform4fv( camPosUniformID, 1, camPos);

	GLuint MaterialID = glGetUniformLocation( m_iLab09ShaderID,"materialDiffuse" );

	int iNumBones	= m_oScene.GetSkeletonByIndex(0)->m_boneCount;
	GLuint boneID	= glGetUniformLocation( m_iLab09ShaderID, "boneArray" );
	glUniformMatrix4fv(boneID, iNumBones, true, *m_oScene.GetSkeletonByIndex(0)->m_bones );

	for(unsigned int i = 0; i < m_oScene.GetMeshCount(); ++i)
	{
		FBXMeshNode* pMesh = m_oScene.GetMeshByIndex(i);

		// get the render object IDs stored in the mesh's user data
		RenderObject* ro = (RenderObject*)pMesh->m_userData;

		// set the mesh's material in the shader
		glUniform4fv(MaterialID, 1, &(pMesh->m_material->diffuse.x));

		// set the mesh's textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::DiffuseTexture] );
		glActiveTexture(GL_TEXTURE1);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::NormalTexture] );
		glActiveTexture(GL_TEXTURE2);
		glBindTexture( GL_TEXTURE_2D, pMesh->m_material->textureIDs[FBXMaterial::SpecularTexture] );

		// apply the meshes global transform
		glUniformMatrix4fv( ModelID, 1, false, pMesh->m_globalTransform );

		// bind buffers and draw
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, pMesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	//Draw the Plane
	SetShader(m_iBasicShaderID);

	std::vector<MeshNode*>::iterator iter;
	iter = m_apoLab09NodesToRender.begin();

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	int i = 0;
	while( iter != m_apoLab09NodesToRender.end() )
	{
		(*iter)->Draw();
		++iter;
		++i;
	}
}

void CRenderManager::DrawParticles( AIE::mat4 a_cameraMatrix )
{
	auto pIter = m_ParticleManagers.find( m_iCurrentStateID );
	if( pIter != m_ParticleManagers.end() )
	{
		std::vector<ParticleSystem*> systems = (*pIter).second->GetActiveEmitters();
		auto sIter = systems.begin();
		while ( sIter != systems.end() )
		{
			if ( (*sIter)->Is3D() )
			{
				SetShader(m_iParticle3DShaderID);
				GLuint ProjectionID = glGetUniformLocation(	m_iParticle3DShaderID, "Projection" );
				glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
				GLuint ViewID = glGetUniformLocation(	m_iParticle3DShaderID, "View" );
				glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
				GLuint ModelID = glGetUniformLocation(	m_iParticle3DShaderID, "Model" );
				glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );
				GLuint CameraPosID = glGetUniformLocation( m_iParticle3DShaderID,	"CameraMat"	);
				glUniformMatrix4fv( CameraPosID, 1, false, a_cameraMatrix	);
				GLuint TimeID = glGetUniformLocation( m_iParticle3DShaderID,	"Time"	);
				glUniform1f( CameraPosID, m_fTimer	);

				glFrontFace( GL_CW );
			}
			else
			{
				SetShader(m_iParticle2DShaderID);
				GLuint texUniformID = glGetUniformLocation( m_iParticle2DShaderID, "diffuseTexture" );
				glUniform1i(texUniformID,0);
				GLuint ProjectionID = glGetUniformLocation(	m_iParticle2DShaderID, "Projection" );
				glUniformMatrix4fv( ProjectionID, 1, false, m_projectionMatrix );
				GLuint ViewID = glGetUniformLocation(	m_iParticle2DShaderID, "View" );
				glUniformMatrix4fv( ViewID, 1, false, m_viewMatrix );
				GLuint ModelID = glGetUniformLocation(	m_iParticle2DShaderID, "Model" );
				glUniformMatrix4fv( ModelID, 1, false, m_modelMatrix );
				GLuint CameraPosID = glGetUniformLocation( m_iParticle2DShaderID,	"CameraMat"	);
				glUniformMatrix4fv( CameraPosID, 1, false, a_cameraMatrix	);
			}

			(*sIter)->Draw(  m_projectionMatrix, m_viewMatrix, m_modelMatrix, a_cameraMatrix );

			++sIter;
		}

		glFrontFace( GL_CCW );
	}
}