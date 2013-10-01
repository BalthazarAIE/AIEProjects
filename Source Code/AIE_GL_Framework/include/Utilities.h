//////////////////////////////////////////////////////////////////////////
// Author:	Conan Bourke
// Date:	December 4 2012
// Brief:	Utility functions
//////////////////////////////////////////////////////////////////////////
#ifndef __AIEFRAMEWORK_H_
#define __AIEFRAMEWORK_H_
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include "MathHelper.h"

#include <GL\glew.h>

namespace AIE
{

//////////////////////////////////////////////////////////////////////////
struct Vertex
{
	union
	{
		struct  
		{
			vec4 position;
			vec2 uv;
		};
		struct
		{
			float x, y, z, w;
			float u, v;
		};
	};

	bool operator == (const Vertex& rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w && u == rhs.u && v == rhs.v);
	}
};

// loads a texture of various formats
// optionally can fill in the width/height pointers if they are valid
unsigned int LoadTexture(const char* a_szTexture, unsigned int a_uiFormat = GL_RGBA, unsigned int* a_uiWidth = nullptr, unsigned int* a_uiHeight = nullptr);

// creates a shader program using the specified shader code files and a list of input attributes and output attributes
unsigned int LoadShader(unsigned int a_uiInputAttributeCount, const char** a_aszInputAttributes,
						unsigned int a_uiOutputAttributeCount, const char** a_aszOutputAttributes,
						const char* a_szVertexShader, const char* a_szPixelShader,
						const char* a_szGeometryShader = nullptr,
						const char* a_szTessellationControlShader = nullptr, const char* a_szTessellationEvaluationShader = nullptr);

// helper function for loading shader code into memory
char* FileToBuffer(const char* a_szPath);

// builds a textured plane out of 2 triangles and fills in the vertex array, vertex buffer, and index buffer
void Build3DPlane(float a_fSize, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO);

void BuildArbitraryPlane( float a_fSize, int a_iVertsWidth, int a_iVertsLength, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO );

void BuildCube( float a_fSize, AIE::vec4 a_vPosition, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO);
void BuildBox( float a_fWidth, float a_fHeight, float a_fDepth, AIE::vec4 a_vPosition, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO);
void BuildSkybox( float a_fSize, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO);

// utilities for timing; Get() updates timers and returns time since last Get call
void ResetTimer();
float GetDeltaTime();

// utility for mouse / keyboard movement of a matrix frame (suitable for camera)
void FreeMovement(float a_fDeltaTime, AIE::mat4& a_rmFrame, float a_fSpeed, const AIE::vec4& a_rvUp = AIE::vec4(0,1,0,0));

float fRand( float a_fMin, float a_fMax );
AIE::vec2 v2Rand( AIE::vec2 a_vMin, AIE::vec2 a_vMax );
AIE::vec4 v4Rand( AIE::vec4 a_vMin, AIE::vec4 a_vMax );

}//namespace AIE

//////////////////////////////////////////////////////////////////////////
#endif // __AIEFRAMEWORK_H_
//////////////////////////////////////////////////////////////////////////