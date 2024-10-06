#include "Rays.hpp"

Rays::Rays()
{
}

Rays::~Rays() {}

void Rays::checkHorizontalLines(Map const &map, Player const &player)
{
	int mapX, mapY, mapPlayer, dephOfField;
	for (int i = 0; i < 60; i++)
	{
		float aTan = -1 / tan(_rayAngle);

		_distanceH = 1000000;
		_horizontalX = player.getPlayerPosX();
		_horizontalY = player.getPlayerPosY();
		dephOfField = 0;
		if (_rayAngle > PI)
		{
			_rayY = (((int)player.getPlayerPosY() >> 6) << 6) -0.0001;
			_rayX = (player.getPlayerPosY() - _rayY) * aTan + player.getPlayerPosX();
			_yOffSet = -64;
			_xOffSet = -_yOffSet * aTan;
		}

		if (_rayAngle < PI)
		{
			_rayY = (((int)player.getPlayerPosY() >> 6) << 6) + 64;
			_rayX = (player.getPlayerPosY() - _rayY) * aTan + player.getPlayerPosX();
			_yOffSet = 64;
			_xOffSet = -_yOffSet * aTan;
		}

		if (_rayAngle == 0 || _rayAngle == PI)
		{
			_rayX = player.getPlayerPosX();
			_rayY = player.getPlayerPosY();
			dephOfField = 8;
		}

		while (dephOfField < 8)
		{
			mapX = (int)(_rayX) >> 6;
			mapY = (int)(_rayY) >> 6;
			mapPlayer = mapY * map.getMapWidth() + mapX;
			if (mapPlayer > 0 && mapPlayer < map.getMapWidth() * map.getMapHeight() && map._map[mapPlayer] == 1)
			{
				_horizontalX = _rayX;
				_horizontalY = _rayY;
				_distanceH = firstHitWall(player.getPlayerPosX(), player.getPlayerPosY(), _horizontalX, _horizontalY);
				dephOfField = 8;
			}
			else
			{
				_rayX += _xOffSet;
				_rayY += _yOffSet;
				dephOfField += 1;
			}
		}
		checkVerticalLines(map, player);

		if (_distanceV < _distanceH)
		{
			_rayX = _verticalX;
			_rayY = _verticalY;
			_finalDist = _distanceV;
		}
		else
		{
			_rayX = _horizontalX;
			_rayY = _horizontalY;
			_finalDist = _distanceH;
		}
		glColor3f(1, 0, 0);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(player.getPlayerPosX(), player.getPlayerPosY());
		glVertex2i(_rayX, _rayY);
		glEnd();

		draw3DMap(map, player, i);

		_rayAngle += DR;
		if (_rayAngle < 0)
			_rayAngle += PI4;
		if (_rayAngle > PI4)
			_rayAngle -= PI4;
	}
}

void Rays::checkVerticalLines(Map const &map, Player const &player)
{
	float aTan = -tan(_rayAngle);
	int mapX, mapY, mapPlayer, dephOfField = 0;
	if (_rayAngle > PI2 && _rayAngle < PI3)
	{
		_rayX = (((int)player.getPlayerPosX() >> 6) << 6) - 0.0001;
		_rayY = (player.getPlayerPosX() - _rayX) * aTan + player.getPlayerPosY();
		_xOffSet = -64;
		_yOffSet = -_xOffSet * aTan;
	}

	if (_rayAngle < PI2 || _rayAngle > PI3)
	{
		_rayX = (((int)player.getPlayerPosX() >> 6) << 6) + 64;
		_rayY = (player.getPlayerPosX() - _rayX) * aTan + player.getPlayerPosY();
		_xOffSet = 64;
		_yOffSet = -_xOffSet * aTan;
	}

	if (_rayAngle == 0 || _rayAngle == PI)
	{
		_rayX = player.getPlayerPosX();
		_rayY = player.getPlayerPosY();
		dephOfField = 8;
	}

	while (dephOfField < 8)
	{
		mapX = (int)(_rayX) >> 6;
		mapY = (int)(_rayY) >> 6;
		mapPlayer = mapY * map.getMapWidth() + mapX;
		if (mapPlayer > 0 && mapPlayer < map.getMapWidth() * map.getMapHeight() && map._map[mapPlayer] == 1)
		{
			_verticalX = _rayX;
			_verticalY = _rayY;
			_distanceV = firstHitWall(player.getPlayerPosX(), player.getPlayerPosY(), _verticalX, _verticalY);
			dephOfField = 8;
		}
		else
		{
			_rayX += _xOffSet;
			_rayY += _yOffSet;
			dephOfField += 1;
		}
	}
}

void Rays::draw3DMap(Map const &map, Player const &player, int i)
{
	(void)player;
	_lineHeight = (map.getMapSize() * 320) / _finalDist;
	if (_lineHeight > 320)
		_lineHeight = 320;
	_lineOffSet = 160 - _lineHeight / 2;
	glLineWidth(8);
	glBegin(GL_LINES);
	glVertex2i(i * 8 + 530, _lineOffSet);
	glVertex2i(i * 8 + 530, _lineOffSet + _lineHeight);
	glEnd();
}

float Rays::firstHitWall(float ax, float ay, float bx, float by)
{
	return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}

void Rays::drawRays3D(Map const &map, Player const &player)
{
	_rayAngle = player.getPlayerAngle() - DR30;
	if (_rayAngle < 0)
		_rayAngle += PI4;
	if (_rayAngle > PI4)
		_rayAngle -= PI4;
	checkHorizontalLines(map, player);
}