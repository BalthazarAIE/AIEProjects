#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL\glfw.h>
#include <FreeImage.h>

#include "TextFileReader.h"

//global window open Flag 
bool g_bWindowClosed = false; 
bool g_bFullscreen = false; 

const char* a_pWindowTitle = "Justin's Window!";

static int GLFWCALL windowCloseListener() 
{ 
	g_bWindowClosed = true; 
	return 0; 
} 


struct V_4f_4f 
{ 
	GLfloat fVertices[4]; 
	GLfloat fUV[2];

}; 

void printProgramInfoLog(GLuint obj);

GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat , unsigned int* a_uiWidth , unsigned int* a_uiHeight, unsigned int* a_uiBPP  );
void printShaderInfoLog(GLuint obj);
int main(int argc, char *argv[])
{
	//We need to call glfwInit() to init GLFW if this returns a value other than 
	// 0 we have been unable to create a window or OpenGL context 
	if( !glfwInit() ) 
	{ 
		return -1; 
	} 


	//This is a Window hint to tell GLFW that we do not wish to allow our window to 
	//be resizeable 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE); 
	//This is the call to GLFW to open our window 
	glfwOpenWindow( 1024, 768, // resolution 
		8,8,8,8, // bits per colour channel (RGBA) 
		24, // depth bits 
		8, // stencil bits 
		(g_bFullscreen)? GLFW_FULLSCREEN:GLFW_WINDOW); 
	//Here we are setting the title for our window 
	glfwSetWindowTitle((a_pWindowTitle != NULL)? a_pWindowTitle : "GLFW Window"); 
	glfwSwapInterval(0); 
	//set listeners for window events such as close window 
	//windowCloseListener is a static function that will be called when the close 
	//button on the window is clicked 
	glfwSetWindowCloseCallback(&windowCloseListener); 

	if (glewInit() != GLEW_OK) 
	{ 
		// OpenGL didn't start-up! shutdown GLFW and return an error code 
		glfwTerminate(); 
		return -1; 
	}
	//Set the clear colour for OpenGL 
	glClearColor( 0.f, 0.4f, 0.65f, 1.f); 
	glColor4f( 0.f, 0.f, 0.f, 1.f ); 
	//As we're going to draw in 2D set up an orthographic projection. 
	//This type of projection has no perspective. This projection is set up so 
	//that one pixel on the screen is one unit in 
	//world co-ordinates 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	//Older versions of OpenGL allow you to set up a view matrix with the following 
	//call. 
	//this function is no longer supported in more recent versions of OpenGL 
	glOrtho( 0.f, 1024, 768, 0.f, 0.f, 100.f ); 
	//Enable some Blending. 
	glEnable(GL_BLEND); 
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

	glEnable(GL_DEPTH); 
	glDepthFunc(GL_LEQUAL); 
	//\================================================================================== 
	//\Create an instance of and Fill our Vertex Structure 
	//\================================================================================== 
	V_4f_4f* pObject = new V_4f_4f[4]; 
	unsigned int uiSize = 512; 


		pObject[0].fVertices[0] = 0; 
		pObject[0].fVertices[1] = 0;
		pObject[0].fVertices[2] = 1;
		pObject[0].fVertices[3] = 1;
		pObject[0].fUV[0] = 0 ;
		pObject[0].fUV[1] = 0;

		
		pObject[1].fVertices[0] = 1; 
		pObject[1].fVertices[1] = 0;
		pObject[1].fVertices[2] = 1;
		pObject[1].fVertices[3] = 1;
		pObject[1].fUV[0] = 1;
		pObject[1].fUV[1] = 0;

		
		pObject[2].fVertices[0] = 0; 
		pObject[2].fVertices[1] = 1;
		pObject[1].fVertices[2] = 1;
		pObject[1].fVertices[3] = 1;
		pObject[2].fUV[0] = 0;
		pObject[2].fUV[1] = 1;

		
		pObject[3].fVertices[0] = 1; 
		pObject[3].fVertices[1] = 1;
		pObject[1].fVertices[2] = 1;
		pObject[1].fVertices[3] = 1; 
		pObject[3].fUV[0] = 1;
		pObject[3].fUV[1] = 1;

	//\================================================================================== 
	//\Request a vertex buffer object from OpenGL 
	//\================================================================================== 
	GLuint VBO; 
	glGenBuffers(1, &VBO); 
	if( VBO != 0 ) 
	{ 
		//\================================================================================== 
		//\If we have a vertex buffer object then we need to fill it with our vertex data 
		//\================================================================================== 
		glBindBuffer( GL_ARRAY_BUFFER, VBO ); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(V_4f_4f) * 4, NULL, GL_STATIC_DRAW ); 
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY ); 
		memcpy(vBuffer, pObject, sizeof(V_4f_4f) * 4); 
		glUnmapBuffer(GL_ARRAY_BUFFER); 
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
	} 


	GLuint v, f, p;
	 std::string vString, fString;
	 const char *vs, *fs;

	// Create shader handlers
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER); 

	// Read source code from files
	vString = textFileReader("./resources/exampleVert.glsl");
	fString = textFileReader("./resources/exampleFrag.glsl");

	vs = vString.c_str();
	fs = fString.c_str();

	// Set shader source
	glShaderSource(v, 1, &vs,NULL);
	glShaderSource(f, 1, &fs,NULL);



	// Compile all shaders
	glCompileShader(v);
	printShaderInfoLog(v);
	glCompileShader(f);
	printShaderInfoLog(f);

	// Create the program
	p = glCreateProgram();

	// Attach shaders to program
	glAttachShader(p,v);
	glAttachShader(p,f);

	// Link and set program to use
	glLinkProgram(p);
	 printProgramInfoLog(p);
	glUseProgram(p);
	unsigned int width=512, height=512;
	glBindBuffer(GL_ARRAY_BUFFER, VBO ); 

	GLuint uiTexture = LoadTexture("./resources/doge.png",GL_RGBA,&width,&height, nullptr);
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, uiTexture );

		
		glUniform1i(glGetUniformLocation(p, "tex"), 0);


	GLint texAttrib = glGetAttribLocation( p, "texcoord" );
	glEnableVertexAttribArray( texAttrib );

	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(4* sizeof(float)) );
	

	while ( glfwGetWindowParam( GLFW_OPENED ) != 0 && !g_bWindowClosed ) 
	{ 
		/* Render here */ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
		//=============================================================================== 
		//Draw a Square 
		//\ -- Here we are utilising A Vertex Buffer Object to draw our vertices 
		//=============================================================================== 
		glBindBuffer(GL_ARRAY_BUFFER, VBO ); 

	

		glEnableClientState(GL_VERTEX_ARRAY); 
		glVertexPointer(4,GL_FLOAT, sizeof(V_4f_4f), NULL ); 

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
 
		glDisableClientState(GL_VERTEX_ARRAY); 
		glBindBuffer(GL_ARRAY_BUFFER, 0); 


		/* Swap front and back buffers and process events */ 
		glfwSwapBuffers(); 
	} 

	// shutdown GLFW 
	glfwTerminate(); 

	return 0; 
}

	void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
    printf("%s\n",infoLog);
        free(infoLog);
    }
}

	void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
    printf("%s\n",infoLog);
        free(infoLog);
    }
}
	GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat /* = 
																	GL_RGBA */, unsigned int* a_uiWidth /* = nullptr */, unsigned int* a_uiHeight /* = 
																	nullptr */, unsigned int* a_uiBPP  = nullptr)
{
	FIBITMAP* pBitmap = nullptr;
	// check the file signature and deduce its format and load it
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(a_szTexture, 0);
	if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) 
	{
		pBitmap = FreeImage_Load(fif, a_szTexture);
	}
	if(pBitmap == nullptr) 
	{
		printf("Error: Failed to load image '%s'!\n", a_szTexture);
		return 0;
	}

	// optionally get the image width and height
	if(a_uiWidth != nullptr)
		*a_uiWidth = FreeImage_GetWidth(pBitmap);

	if(a_uiHeight != nullptr)
		*a_uiHeight = FreeImage_GetHeight(pBitmap);

	// force the image to RGBA
	unsigned int bpp = FreeImage_GetBPP(pBitmap);


	if( a_uiBPP != nullptr )
		*a_uiBPP = bpp/8;
	FREE_IMAGE_COLOR_TYPE fi_colourType = FreeImage_GetColorType(pBitmap);

	if(fi_colourType != FIC_RGBALPHA ) 
	{
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(pBitmap);
		FreeImage_Unload(pBitmap);
		pBitmap = ndib;
		bpp = FreeImage_GetBPP(pBitmap);
		fi_colourType = FreeImage_GetColorType(pBitmap);
	}

	// get the pixel data
	BYTE* pData = FreeImage_GetBits(pBitmap);

	// try to determine data type of file (bytes/floats)
	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(pBitmap);
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT) ? GL_FLOAT:GL_UNSIGNED_BYTE;

	// create GL texture
	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
		FreeImage_GetWidth(pBitmap), 
		FreeImage_GetHeight(pBitmap), 0, 
		a_uiFormat, eType, pData);

	// specify default filtering and wrapping
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// unbind texture
	glBindTexture( GL_TEXTURE_2D, 0 );
	// delete data
	FreeImage_Unload(pBitmap);
	return textureID;
}