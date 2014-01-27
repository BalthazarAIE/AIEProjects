#ifndef _UTIL_H_
#define _UTIL_H_
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>

//Terry's Math lib
#include <TerrehByteMath.h>
//other helper functions
#include "GLLog.h"
#include "TextFileReader.h"


#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>


struct Vertex
{
	union
	{
		struct 
		{
			tbyte::Vector4 Pos;
			tbyte::Vector4 Color;
			tbyte::Vector2 UV;
		};
		
		/*struct
		{
			float X, Y, Z, W;
			float R, G, B, A;
			float U, V;
		};*/
	};
};

GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat , unsigned int* a_uiWidth , unsigned int* a_uiHeight, unsigned int* a_uiBPP  );
void printShaderInfoLog(GLuint obj);

#endif