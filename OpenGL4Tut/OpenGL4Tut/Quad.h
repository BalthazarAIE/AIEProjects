#ifndef _QUAD_
#define _QUAD_

#include <GL\glew.h> //Or wherever your Glew is located
#include <GLLog.h> //For logging… stuff
#include <TextFileReader.h>

class Quad
{
public:
	Quad(void);
	~Quad(void);

	int m_iVertexCount;

	float m_afVertexArray[12];
	float m_afColorArray[16];
	float m_afUVArray[8];

	GLuint m_VBO;
	GLuint m_CBO;
	GLuint m_UBO;
	GLuint m_VAO;
	GLuint m_EBO;
	
	GLuint m_FragmentShader;
	GLuint m_VertexShader;

	GLuint m_ShaderProgram;

	void Draw();
private:

};
#endif // _QUAD_
