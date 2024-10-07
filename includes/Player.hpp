#pragma once

#include "Utils.hpp"

class Player
{
public:
	Player(sf::Vector2f position);
	Player(Player const &obj);
	Player &operator=(Player const &obj);
	~Player();

	void draw(sf::RenderTarget &target);
	void update(float deltaTime);
	sf::Vector2f position;
	float angle;
};