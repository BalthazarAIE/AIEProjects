#include <GL\glew.h>
#include <GL\wglew.h>

#define GLFW_DLL
#include <GL\glfw3.h>
#include <glm.hpp>
#include "math_funcs.h"

#include <stdio.h>
#include "GLLog.h"


void printProgramInfoLog(GLuint obj);
void printShaderInfoLog(GLuint obj);
void log_gl_params ();

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;

// a call-back function
void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;

	/* update any perspective matrices used here */
}

//call back before initalization of GLFW
void glfw_error_callback (int error, const char* description) {
	fputs (description, stderr);
	gl_log (description, __FILE__, __LINE__);
}

int main()
{
	//setup to log some GLFW stuff

	char message[256];
	sprintf (message, "starting GLFW %s", glfwGetVersionString ());
	assert (gl_log (message, __FILE__, __LINE__));
	glfwSetErrorCallback (glfw_error_callback);



	//open an OS window using GLFW
	if(!glfwInit())
	{
		fprintf (stderr,"ERROR: could not start GLFW3\n");
		return 1;
	}

	// uncomment these lines if on Apple OS X
	/*	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/	
	//Anti-Aliasing
	glfwWindowHint (GLFW_SAMPLES, 4);

	//get the primary monitor
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	//this lets us the the video mode for the monitor we pass
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	GLFWwindow* window = glfwCreateWindow (
		vmode->width, vmode->height, "Extended GL Init",NULL/* mon*/, NULL
		);
	glfwSetWindowSize(window, 640, 480);

	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	//not sure if this works
	//log_gl_params ();

	glfwMakeContextCurrent(window);

	//start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	float points[] = 
	{
		0.0f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,

	};
	float colors[] = 
	{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};

	//Column Major Order 
	float matrix[] =
	{
		1.0,0.0f,0.0f,0.0f, //first column
		0.0,1.0f,0.0f,0.0f, //second column
		0.0,0.0f,1.0f,0.0f, //third column
		0.5,0.0f,0.0f,1.0f  //fourth column
	};

	GLuint pointsVBO = 0;
	glGenBuffers (1, &pointsVBO);
	glBindBuffer (GL_ARRAY_BUFFER, pointsVBO);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

	GLuint colorsVBO = 0;
	glGenBuffers (1, &colorsVBO);
	glBindBuffer (GL_ARRAY_BUFFER, colorsVBO);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), colors, GL_STATIC_DRAW);

	unsigned int VAO = 0;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	glBindBuffer (GL_ARRAY_BUFFER, pointsVBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer (GL_ARRAY_BUFFER, colorsVBO);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	const char* vertex_shader =
		"layout(location = 0) in vec3 vertex_position;\n"
		"layout(location = 1) in vec3 vertex_color;\n"
		"uniform mat4 matrix; //out matrix \n"
		"out vec3 color;\n"
		"void main () {\n"
		"color = vertex_color;\n"
		"gl_Position = matrix * vec4 (vertex_position, 1.0);\n"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"in vec3 color;\n"
		"out vec4 frag_color;\n"

		"void main () {\n"
		"  frag_color = vec4 (color, 1.0);\n"
		"}";

	//Create a shader
	unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
	//put the actual char* into the shader 
	glShaderSource (vs, 1, &vertex_shader, NULL);
	//Compile the shader 
	glCompileShader (vs);
	//Prints out some info if the compile didnt work
	printShaderInfoLog(vs);

	unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	printShaderInfoLog(fs);

	//Create the container that holds your shaders
	unsigned int shaderProgram = glCreateProgram ();
	//attach the shaders you compiled
	glAttachShader (shaderProgram, fs);
	glAttachShader (shaderProgram, vs);


	glBindAttribLocation(shaderProgram, 0,"vertex_position");
	glBindAttribLocation(shaderProgram, 1,"vertex_colour");
	//this is links the shaders together, its kinda like a compile
	glLinkProgram (shaderProgram);
	//also prints out a log
	printProgramInfoLog(shaderProgram);

	float speed = 1.0f; // move at 1 unit per second
float last_position = 0.0f;
int matrix_location = glGetUniformLocation (shaderProgram, "matrix");
	while (!glfwWindowShouldClose (window)) {

		// add a timer for doing animation
  static double previous_seconds = glfwGetTime ();
  double current_seconds = glfwGetTime ();
  double elapsed_seconds = current_seconds - previous_seconds;
  previous_seconds = current_seconds;
   // reverse direction when going to far left or right
  if (fabs(last_position) > 1.0f) {
    speed = -speed;
  }

		glEnable (GL_CULL_FACE); // cull face
		glCullFace (GL_BACK); // cull back face
		glFrontFace (GL_CW); // GL_CCW for counter clock-wise

		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//resize window
		glViewport (0, 0, g_gl_width, g_gl_height);

	
		
		  // update the matrix
  matrix[12] = elapsed_seconds * speed + last_position;
  last_position = matrix[12];
		//set the shader for this VAO
		glUseProgram (shaderProgram);
		//Here is where we attach the marix
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, matrix);
		//bind the VAO to be drawn
		glBindVertexArray (VAO);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, 3);
		// update other events like input handling 
		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (window);


		//When do i exit?
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		}
	}

	// close GL context and any other GLFW resources
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

void log_gl_params () {
	GLenum params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	gl_log ("GL Context Params:", __FILE__, __LINE__);
	char msg[256];
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		sprintf (msg, "%s %i", names[i], v);
		gl_log (msg, __FILE__, __LINE__);
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	sprintf (msg, "%s %i %i", names[10], v[0], v[1]);
	gl_log (msg, __FILE__, __LINE__);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	sprintf (msg, "%s %i", names[11], (unsigned int)s);
	gl_log (msg, __FILE__, __LINE__);
	gl_log ("-----------------------------", __FILE__, __LINE__);
}