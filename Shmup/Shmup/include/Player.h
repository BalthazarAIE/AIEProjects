#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Entity.h"
#include "Bullet.h"
#include <list>
const float PLAYER_SPEED = .5f;

class Player :
	public Entity
{
public:
	Player(void);
	~Player(void);
	void Input();
	void Update();

	void AddXp(xp amount); 
private:
	xp m_xTotalXp;
	std::list<Bullet> m_lBullets;

};

#endif //_PLAYER_H_