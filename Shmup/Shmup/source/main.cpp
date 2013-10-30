//////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "Player.h"
#include "Globals.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>



//Declaring an enum for Game States
typedef enum GameStates
{
	MENU_STATE,
	PLAY_STATE,
	WIN_STATE,
	LOSE_STATE
}GameState;




int main( int argc, char* argv[] )
{	
	Initialise( SCREEN_WIDTH,SCREEN_HEIGHT, false, "Tony Demo" );
	
	Sprite sBackground = Sprite();
	sBackground.Init("./images/Space_Background.png", SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_WIDTH,SCREEN_HEIGHT);
	sBackground.SetPos(Vector2(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));

	Player *pPlayer = new Player();
	pPlayer->Init("./images/crate_sideup.png",50,50,50,50);
	pPlayer->SetPos(Vector2(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
	GameState eCurrentState = PLAY_STATE;
	
	Entity *BadGuy = new Entity();

	pPlayer->AddXp(100);
	

	do 
	{
		
		//Test the current game state
		switch(eCurrentState)
		{
	
		case PLAY_STATE:
		{
			sBackground.Draw();
			pPlayer->Update();
			
			break;
		}
		default:
			break;
		}//End of Switch Statement


	} while ( FrameworkUpdate() == false );
	
	delete BadGuy;
	delete pPlayer;
	Shutdown();

	return 0;
}

