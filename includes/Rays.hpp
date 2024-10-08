#pragma once

#include <Utils.hpp>

class Player;
class Map;

class Rays
{
private:

public:
	Rays();
	~Rays();

	void drawRays(sf::RenderTarget &target, const Player &player, const Map &map);
};