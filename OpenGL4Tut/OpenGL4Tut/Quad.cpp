#include "Quad.h"


Quad::Quad(void)
{
	
	m_iVertexCount = 4;

	GLfloat vertices[] = 
	{
        -0.25f,  0.25f, 0.0, 1.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, // Top-left
         0.25f,  0.25f, 0.0, 0.0f, 1.0f, 0.0f, 1.0, 1.0f, 0.0f, // Top-right
         0.25f, -0.25f, 0.0, 0.0f, 0.0f, 1.0f, 1.0, 1.0f, 1.0f, // Bottom-right
        -0.25f, -0.25f, 0.0, 1.0f, 1.0f, 1.0f, 1.0, 0.0f, 1.0f  // Bottom-left
	};

	//Default Shaders for Default constructor

		const char * VertexShader =	// Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"in vec3 vertexPosition;"
		"in vec4 vertexColor;"
		"out vec4 vColor;"
		"void main() {"
		"	vColor = vertexColor;"
		"	gl_Position = vec4 (vertexPosition, 1.0);"
		"}";

	const char * FragmentShader =	// Fragment Shaders dela with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vColor;"
		"}";

	//======================== 
	// Create the VAO
	//========================

	m_VAO = 0;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		//======================== 
	// Create the VBO
	//========================

	m_VBO = 0;
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER,
				 m_iVertexCount * sizeof(float),
				 m_afVertexArray,
				 GL_STATIC_DRAW);



	//======================== 
	// Create the SHADERS
	//========================

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);


	GLint posAttrib = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(
		posAttrib,				//the attributes location in the shader program
		3,						//how many units are in this attribute
		GL_FLOAT,				//type of units
		GL_FALSE,				//Are these units normalized, prolly most likely false
		(9 * sizeof(float)),	//How many points of data are in a vertex this case vec3 + vec4 + vec2 = 9
		0						//A pointer to the start of the data 
		);
		
	GLint colorAttrib = glGetAttribLocation(m_ShaderProgram, "vertexColor");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(
		colorAttrib,			//the attributes location in the shader program
		4,						//how many units are in this attribute
		GL_FLOAT,				//type of units
		GL_FALSE,				//Are these units normalized, prolly most likely false
		(9 * sizeof(float)),	//How many points of data are in a vertex this case vec3 + vec4 + vec2 = 8
		(void*)(3*sizeof(float))//A pointer to the start of the data
		);
}


Quad::~Quad(void)
{

}

void Quad::Draw()
{
	glUseProgram(m_ShaderProgram);

	glBindVertexArray(m_VAO);

	glDrawArrays(GL_TRIANGLE_STRIP,
				 0,
				 m_iVertexCount);	

}