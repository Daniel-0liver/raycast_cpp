#pragma once

#include <Utils.hpp>

class Player;
class Map;

struct Ray
{
	sf::Vector2f hitPosition;
	float distance;
	bool isHit;
};

class Rays
{
private:

public:
	Rays();
	~Rays();

	void drawRays2D(sf::RenderTarget &target, const Player &player, const Map &map);
	void drawRays3D(sf::RenderTarget &target, const Player &player, const Map &map);
	static Ray castRay(sf::Vector2f start, const Map &map, float angleInDegrees);
};