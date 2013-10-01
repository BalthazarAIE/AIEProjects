#include "CApplication.h"

int main( int argc, char** argv )
{
	bool bFullScreen = false;

	CApplication* pApp = new CApplication(1280, 720, bFullScreen);

	pApp->Run();

	delete pApp;

	return 0;
}