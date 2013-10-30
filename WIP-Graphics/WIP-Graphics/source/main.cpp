//////////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>
#include <vector>
#include "Utilities.h"
#include "Camera.h"

#include "PlaneNode.h"//Use your Mesh instead;





using namespace AIE;

//////////////////////////////////////////////////////////////////////////
void InitOpenGL();

void Run();
void Update(float fDeltaTime);
void Draw();
void MakeStuff();
void LoadBasicShader();

bool m_bFullscreen = false;
Camera* m_poCamera;
PlaneNode*	m_poWaterPlane;
Quaternion	m_qPlaneRot;
SceneNode* g_Scene;
std::vector<MeshNode*>	NodesToRender;

	mat4					m_projectionMatrix;
	mat4					m_viewMatrix;
	mat4					m_modelMatrix;
	mat4					m_cameraMatrix;

		GLuint					m_iBasicShaderID;

			GLuint					m_iProjectionID;
	GLuint					m_iViewID;
	GLuint					m_iModelID;		
	GLuint					m_iTimeID;
	GLuint					m_iColourID;

//////////////////////////////////////////////////////////////////////////
int main(int argc, TCHAR * argv[] )
{

	g_Scene = new SceneNode(vec4(0,0,0,0),nullptr);


	
	Run();




	// shutdown GLFW
	glfwTerminate();

	// return success
	return 0;
}
void MakeStuff()
{
	m_poCamera = new Camera();
	m_poCamera->SetCameraPosition( AIE::vec4(0.f, 7.f, -80.f, 1.f) );
	
	m_poWaterPlane = new PlaneNode(100.f, 100.f, 100, 100, AIE::vec4(0.f, 0.f, 0.f, 1.f));
	m_poWaterPlane->SetTexture( LoadTexture("./resources/images/crate_sideup.png") );
	


	NodesToRender.push_back(m_poWaterPlane);
}

//////////////////////////////////////////////////////////////////////////
void InitOpenGL()
{
	// start GLFW and open a window
	glfwInit();

	// get the desktop mode
	GLFWvidmode oMode;
	glfwGetDesktopMode(&oMode);

	// open a window
	glfwOpenWindow(	1280, 720,	// resolution
					oMode.RedBits,oMode.GreenBits,oMode.BlueBits,0,	// bits per colour channel (RGBA)
					24,			// depth bits
					8,			// stencil bits
					m_bFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW); // set windowed or fullscreen mode);
	glfwSetWindowTitle("New AIE Framework");

	// start GLEW
	if (glewInit() != GLEW_OK)
	{	// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
	}



	// set clear colour
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// start our timer
	AIE::ResetTimer();
}

void Run()
{
	InitOpenGL();
	MakeStuff();

	do
	{
		float fDeltaTime = AIE::GetDeltaTime();
		if( fDeltaTime > 1/60.f )
			fDeltaTime = 1/60.f;

		glClear(GL_COLOR_BUFFER_BIT);
	
		Update(fDeltaTime);
		
		Draw();

		glfwSwapBuffers();
	} while ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_RELEASE &&
		glfwGetWindowParam( GLFW_OPENED ) != 0 );
	
}
//////////////////////////////////////////////////////////////////////////
void Update(float fDeltaTime)
{
	fDeltaTime = GetDeltaTime();

 

	
}

//////////////////////////////////////////////////////////////////////////
void Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	LoadBasicShader();
	std::vector<MeshNode*>::iterator iter = NodesToRender.begin();
	while(iter != NodesToRender.end())
	{
		(*iter)->Draw();
	}
}

//////////////////////////////////////////////////////////////////////////

void LoadBasicShader()
{
	const char* aszStandardInputs[]		= { "Position",	"UV"	};
	const char* aszStandardOutputs[]	= { "outColour"			};

	m_iBasicShaderID			= LoadShader(	2, aszStandardInputs, 0, aszStandardOutputs,
												"./resources/shaders/basic_vertex.glsl",
												"./resources/shaders/basic_fragment.glsl"
											/*	,"./resources/shaders/basic_geometry.glsl",
												"./resources/shaders/basic_tess_control.glsl",
												"./resources/shaders/basic_tess_eval.glsl"*/
												);

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
