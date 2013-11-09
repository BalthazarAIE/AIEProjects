#ifndef _LINE2_H_
#define _LINE2_H_
#include "Vector2.h"

class Line2
{
public:
	Line2(void);
	Line2(Vector2 a_vPointOne, Vector2 a_vPointTwo);
	~Line2(void);
	Vector2 PointOne;
	Vector2 PointTwo;
};
#endif //_LINE2_H_
