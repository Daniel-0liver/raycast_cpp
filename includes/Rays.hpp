#pragma once

#include <Utils.hpp>

class Player;
class Map;

class Rays
{
private:
	float	_rayX;
	float	_rayY;
	float	_rayAngle;
	float	_xOffSet;
	float	_yOffSet;
	float	_distanceH;
	float	_horizontalX;
	float	_horizontalY;
	float	_distanceV;
	float	_verticalX;
	float	_verticalY;
	float	_lineHeight;
	float	_lineOffSet;
	int		_finalDist;	
public:
	Rays();
	~Rays();

	void drawRays3D(Map const &map, Player const &player);
	void checkHorizontalLines(Map const &map, Player const &player);
	void checkVerticalLines(Map const &map, Player const &player);
	float firstHitWall(float ax, float ay, float bx, float by);
	void draw3DMap(Map const &map, Player const &player, int i);
};