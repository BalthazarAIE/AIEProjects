#include "Player.h"



Player::Player(void)
{
	Respawn();
	GetCollider().SetRadius(50);
	m_lBullets = std::vector<Bullet *>(4,new Bullet());
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
	if(m_oCollider.CollisionCheck(Vector2(0,0),Vector2(0,SCREEN_HEIGHT)))
	{
		GetVel().SetX(0);
		SetPos(GetPos()+Vector2(1,0));
	}
	if(GetCollider().CollisionCheck(Vector2(SCREEN_WIDTH,0),Vector2(SCREEN_WIDTH,SCREEN_HEIGHT)))
	{
		GetVel().SetX(0);
		SetPos(GetPos()+Vector2(-.5,0));
	}
	if(GetCollider().CollisionCheck(Vector2(0,0),Vector2(SCREEN_WIDTH,0)))
{
		GetVel().SetY(0);
		SetPos(GetPos()+Vector2(0,1));
	}
	if(GetCollider().CollisionCheck(Vector2(0,SCREEN_HEIGHT),Vector2(SCREEN_WIDTH,SCREEN_HEIGHT)))
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