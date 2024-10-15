#pragma once

#include "Utils.hpp"

class Sprite
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	Sprite();
public:
	Sprite(const std::string &texturePath);
	~Sprite();

	void draw(sf::RenderTarget &target);

	sf::Sprite &getSprite();
	sf::Texture &getTexture();

	void setTexture(const sf::Texture &texture);
	void setPosition(const float x, const float y);
};