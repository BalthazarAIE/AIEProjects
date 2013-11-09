#ifndef _SPRTIE_H_
#define _SPRITE_H_
#include "Vector2.h"

enum PlayType {STATIC,ONCE,LOOP,PINGPONG};


class Sprite 
{
public:
	Sprite(void);
	~Sprite(void);

	void Init(const char *szSpriteSheet,int a_iWidth,int a_iHeight, int a_iSheetWidth,int a_iSheetHeight);
	void Draw();
	void Update();
	
inline Vector2& GetPos(){return m_vPosition;}
inline Vector2& GetVel(){return m_vVelocity;}
inline int& GetWidth(){return m_iWidth;}
inline int& GetHeight(){return m_iHeight;}
inline int& GetSpriteID(){return m_iSpriteID;}

inline void SetPos(Vector2 a_vPos){m_vPosition = a_vPos;}
inline void SetVel(Vector2 a_vVel){m_vVelocity = a_vVel;}
inline void SetWidth(int a_iWidth){m_iWidth = a_iWidth;}
inline void SetHeight(int a_iHeight){m_iHeight = a_iHeight;}
inline void SetSpriteID(int a_iSpriteID){m_iSpriteID = a_iSpriteID;}

	void PlayAnimation(unsigned int * list,unsigned int frames, PlayType type);
	



private:
	Vector2 m_vPosition;
	Vector2 m_vVelocity;
	int m_iSpriteID;
	unsigned int currentFrame,lastFrame; 
	int m_iWidth;
	int m_iHeight;
	int a_iSheetWidth;
	int a_iSheetHeight;

};
#endif //_SPRITE_H_
