#ifndef _SPRTIE_H_
#define _SPRITE_H_
#include "Vector2.h"

enum PlayType {STAIC,ONCE,LOOP,PINGPONG};


class Sprite 
{
public:
	Sprite(void);
	~Sprite(void);

	void Init(const char *szSpriteSheet,int a_iWidth,int a_iHeight, int a_iSheetWidth,int a_iSheetHeight);
	void Draw();
	void Update();
	
	Vector2& GetPos();
	Vector2& GetVel();
	int& GetWidth();
	int& GetHeight();
	int& GetSpriteID();

	void SetPos(Vector2 a_vPos);
	void SetVel(Vector2 a_vVel);
	
	void SetWidth(int a_iWidth);
	void SetHeight(int a_iHeight);
	void SetSpriteID(int a_iSpriteID);
	



private:
	Vector2 m_vPosition;
	Vector2 m_vVelocity;
	int m_iSpriteID;
	int m_iWidth;
	int m_iHeight;
	int a_iSheetWidth;
	int a_iSheetHeight;

};
#endif //_SPRITE_H_
