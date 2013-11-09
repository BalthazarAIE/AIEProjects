#include "Sprite.h"
#include "AIE.h"

Sprite::Sprite(void)
{
	m_vPosition.Zero();
	m_vVelocity.Zero();
	m_iSpriteID = -1;
	m_iWidth = 0;
	m_iHeight = 0;
}



Sprite::~Sprite(void)
{
	/*if(m_iSpriteID != -1) {
		DestroySprite(m_iSpriteID);
	}*/
}
void Sprite::Init(const char *szSpriteSheet,int a_iWidth,int a_iHeight, int a_iSheetWidth,int a_iSheetHeight)
{
	m_iSpriteID = CreateSprite(szSpriteSheet,a_iSheetWidth,a_iSheetWidth,true);
	m_iWidth = a_iWidth;
	m_iHeight = a_iHeight;


}

void Sprite::Draw()
{
	MoveSprite(m_iSpriteID,m_vPosition.GetX(),m_vPosition.GetY());
	DrawSprite(m_iSpriteID);
}

void Sprite::Update()
{
	m_vPosition += m_vVelocity;
}

void PlayAnimation(unsigned int * list,unsigned int frames, PlayType type,float speed)
{
	switch(type)
	{
	case STATIC:
	

	case ONCE:
	case LOOP:
	case PINGPONG:
	default:
		
	}
}


Vector2& Sprite::GetPos(){return m_vPosition;}
Vector2& Sprite::GetVel(){return m_vVelocity;}
int& Sprite::GetWidth(){return m_iWidth;}
int& Sprite::GetHeight(){return m_iHeight;}
int& Sprite::GetSpriteID(){return m_iSpriteID;}

void Sprite::SetPos(Vector2 a_vPos){m_vPosition = a_vPos;}
void Sprite::SetVel(Vector2 a_vVel){m_vVelocity = a_vVel;}
void Sprite::SetWidth(int a_iWidth){m_iWidth = a_iWidth;}
void Sprite::SetHeight(int a_iHeight){m_iHeight = a_iHeight;}
void Sprite::SetSpriteID(int a_iSpriteID){m_iSpriteID = a_iSpriteID;}