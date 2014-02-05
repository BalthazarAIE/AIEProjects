#include <Utilities.h>



	void ViewLookAt( tbyte::Vector4& eye,  tbyte::Vector4& to,  tbyte::Vector4& up,tbyte::Matrix4 & mat)
	{
		tbyte::Vector4 vForward = to- eye;
		vForward.Normalise();
		
		tbyte::Vector4 vLeft =up.CrossProduct(vForward);
		vLeft.Normalise();

		tbyte::Vector4 vUp = vForward.CrossProduct(vLeft);
		
		mat.m_afArray[0] = vLeft.m_fX; 
		mat.m_afArray[4] = vLeft.m_fY; 
		mat.m_afArray[8] = vLeft.m_fZ; 
		mat.m_afArray[12] = -(vLeft.DotProduct(eye));   

		mat.m_afArray[1] = vUp.m_fX;
		mat.m_afArray[5] = vUp.m_fY;
		mat.m_afArray[9] = vUp.m_fZ;
		mat.m_afArray[13] = -(vUp.DotProduct(eye));  

		mat.m_afArray[2] = vForward.m_fX; 
		mat.m_afArray[6] = vForward.m_fY; 
		mat.m_afArray[10] = vForward.m_fZ; 
		mat.m_afArray[14] = -(vForward.DotProduct(eye));   

		mat.m_afArray[3] = 0.0f;
		mat.m_afArray[7] = 0.0f;
		mat.m_afArray[11] = 0.0f;
		mat.m_afArray[15] = 1.0f;
	}
	
	void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar,tbyte::Matrix4 & mat)
	{
		float       deltaX = a_fRight - a_fLeft;
		float       deltaY = a_fTop - a_fBottom;
		float       deltaZ = a_fFar - a_fNear;

		mat.m_afArray[0] = 2.f / deltaX;
		mat.m_afArray[1] = 0.f;
		mat.m_afArray[2] = 0.f;
		mat.m_afArray[3] = 0.f;

		mat.m_afArray[4] = 0.f;
		mat.m_afArray[5] = 2.f / deltaY;
		mat.m_afArray[6] = 0.f;
		mat.m_afArray[7] = 0.f;

		mat.m_afArray[8] = 0.f;
		mat.m_afArray[9] = 0.f;
		mat.m_afArray[10] = -2.f / deltaZ;
		mat.m_afArray[11] = 0.f;

		mat.m_afArray[12] = -((a_fRight + a_fLeft)/deltaX);
		mat.m_afArray[13] = -((a_fTop + a_fBottom)/deltaY);
		mat.m_afArray[14] = -((a_fFar + a_fNear)/deltaZ);
		mat.m_afArray[15] = 1.f;
	}

	void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,tbyte::Matrix4 & mat)
	{
		mat.m_afArray[0] = 2 / a_fWidth;
		mat.m_afArray[1] = 0;
		mat.m_afArray[2] = 0;
		mat.m_afArray[3] = 0;

		mat.m_afArray[4] = 0;
		mat.m_afArray[5] = 2 / a_fHeight;
		mat.m_afArray[6] = 0;
		mat.m_afArray[7] = 0;

		mat.m_afArray[8] = 0;
		mat.m_afArray[9] = 0;
		mat.m_afArray[10] = 1 / (a_fFar - a_fNear);
		mat.m_afArray[11] = 0;

		mat.m_afArray[12] = 0;
		mat.m_afArray[13] = 0;
		mat.m_afArray[14] = a_fNear / (a_fNear - a_fFar);
		mat.m_afArray[15] = 1;
	}

	void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,tbyte::Matrix4 & mat)
	{
		float halfAngleRadians = 0.5f * a_fUpFOV;
		float cot = 1 / tanf(halfAngleRadians);

		mat.m_afArray[0] = cot / a_fAspectRatio;
		mat.m_afArray[1] = 0;
		mat.m_afArray[2] = 0;
		mat.m_afArray[3] = 0;

		mat.m_afArray[4] = 0;
		mat.m_afArray[5] = cot;
		mat.m_afArray[6] = 0;
		mat.m_afArray[7] = 0;

		mat.m_afArray[8] = 0;
		mat.m_afArray[9] = 0;
		mat.m_afArray[10] = a_fFar / (a_fFar - a_fNear);
		mat.m_afArray[11] = 1;

		mat.m_afArray[12] = 0;
		mat.m_afArray[13] = 0;
		mat.m_afArray[14] = a_fNear * a_fFar / (a_fNear - a_fFar);
		mat.m_afArray[15] = 0;
	}



GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat 
					 =GL_RGBA , unsigned int* a_uiWidth  = nullptr , 
					unsigned int* a_uiHeight  = nullptr , unsigned int* a_uiBPP  = nullptr)
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