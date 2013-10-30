#include "Player.h"


Player::Player(void)
{
	Respawn();
	SetRadius(10);
	m_lBullets = std::list<Bullet>(4,Bullet());
}


Player::~Player(void)
{
}


void Player::Input()
{
	if(IsKeyDown('W') || IsKeyDown(KEY_UP))
	{
		GetVel().SetY(-PLAYER_SPEED);
	}
	else if(IsKeyDown('S') || IsKeyDown(KEY_DOWN))
	{
		GetVel().SetY(PLAYER_SPEED);
	}else
	{
		GetVel().SetY(0);
	}

	if(IsKeyDown('A') || IsKeyDown(KEY_LEFT))
	{
		GetVel().SetX(-PLAYER_SPEED);
	}
	else if(IsKeyDown('D') || IsKeyDown(KEY_RIGHT))
	{
		GetVel().SetX(PLAYER_SPEED);
	}else
	{
		GetVel().SetX(0);
	}
}

void Player::Update()
{
	Input();
	if(CollisionCheck(Vector2(0,SCREEN_HEIGHT),Vector2(0,0)))
	{
		GetVel().SetX(0);
		SetPos(GetPos()+Vector2(1,0));
	}
	if(CollisionCheck(Vector2(SCREEN_WIDTH,SCREEN_HEIGHT),Vector2(SCREEN_WIDTH,0)))
	{
		GetVel().SetX(0);
		SetPos(GetPos()+Vector2(-.5,0));
	}
	if(CollisionCheck(Vector2(SCREEN_WIDTH,0),Vector2(0,0)))
{
		GetVel().SetY(0);
		SetPos(GetPos()+Vector2(0,1));
	}
	if(CollisionCheck(Vector2(SCREEN_WIDTH,SCREEN_HEIGHT),Vector2(0,SCREEN_HEIGHT)))
	{
		GetVel().SetY(0);
		SetPos(GetPos()+Vector2(0,-.5));
	}
		Entity::Update();
}
void Player::AddXp(xp XP)
{	
	m_xTotalXp += XP;
}