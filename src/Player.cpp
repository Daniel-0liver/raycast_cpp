#include "Player.hpp"

Player::Player(sf::Vector2f position) : position(position), angle(0.0f)
{
}

Player::Player(Player const &obj)
{
	*this = obj;
}

Player &Player::operator=(Player const &obj)
{
	this->position = obj.position;
	this->angle = obj.angle;
	*this = obj;
	return (*this);
}

Player::~Player() {}

void Player::draw(sf::RenderTarget &target)
{
	sf::CircleShape player(8.0f);
	player.setOrigin(player.getRadius(), player.getRadius());
	player.setPosition(position);
	player.setFillColor(sf::Color::Green);

	sf::RectangleShape line(sf::Vector2f(24.0f, 2.0f));
	line.setPosition(position);
	line.setRotation(angle);
	line.setFillColor(sf::Color::Red);

	target.draw(line);
	target.draw(player);
}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle -= TURN_SPEED * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle += TURN_SPEED * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		float radians = angle * PI / 180.0f;

		position.x += cos(radians) * MOVE_SPEED * deltaTime;
		position.y += sin(radians) * MOVE_SPEED * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		float radians = angle * PI / 180.0f;

		position.x -= cos(radians) * MOVE_SPEED * deltaTime;
		position.y -= sin(radians) * MOVE_SPEED * deltaTime;
	}
}