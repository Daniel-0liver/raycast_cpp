#include "Sprite.hpp"

Sprite::Sprite(const std::string &texturePath)
{
	if (!_texture.loadFromFile(texturePath))
		throw std::runtime_error("Failed to load texture");
	_texture.setRepeated(true);
	_sprite = sf::Sprite(_texture);
}

Sprite::~Sprite() {}

void Sprite::draw(sf::RenderTarget &target)
{
	target.draw(_sprite);
}

sf::Sprite &Sprite::getSprite()
{
	return _sprite;
}

sf::Texture &Sprite::getTexture()
{
	return _texture;
}

void Sprite::setTexture(const sf::Texture &texture)
{
	_sprite.setTexture(texture);
}

void Sprite::setPosition(const float x, const float y)
{
	_sprite.setPosition(x, y);
}