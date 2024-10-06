#include "Player.hpp"

Player::Player() : _playerPosX(300), _playerPosY(300), _velocity(5) 
{
	_playerAngle = 0;
	_playerDeltaX = cos(_playerAngle) * _velocity;
	_playerDeltaY = sin(_playerAngle) * _velocity;
}

Player::Player(Player const &obj)
{
	*this = obj;
}

Player &Player::operator=(Player const &obj)
{
	this->_playerPosX = obj._playerPosX;
	this->_playerPosY = obj._playerPosY;
	return (*this);
}

Player::~Player() {}

// Getters
float Player::getPlayerPosX() const {
    return _playerPosX;
}

float Player::getPlayerPosY() const {
    return _playerPosY;
}

float Player::getPlayerDeltaX() const {
    return _playerDeltaX;
}

float Player::getPlayerDeltaY() const {
    return _playerDeltaY;
}

float Player::getPlayerAngle() const {
    return _playerAngle;
}

float Player::getVelocity() const {
    return _velocity;
}

// Setters
void Player::setPlayerPosX(float posX) {
    _playerPosX = posX;
}

void Player::setPlayerPosY(float posY) {
    _playerPosY = posY;
}

void Player::setPlayerDeltaX(float deltaX) {
    _playerDeltaX = deltaX;
}

void Player::setPlayerDeltaY(float deltaY) {
    _playerDeltaY = deltaY;
}

void Player::setPlayerAngle(float angle) {
    _playerAngle = angle;
}

void Player::setVelocity(float velocity) {
    _velocity = velocity;
}

void Player::drawPlayer()
{
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(_playerPosX, _playerPosY);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(_playerPosX, _playerPosY);
	glVertex2i(_playerPosX + _playerDeltaX * 5, _playerPosY + _playerDeltaY * 5);
	glEnd();
}

void Player::playerMovement(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	if (key == 'a')
	{
		_playerAngle -= 0.1;
		if (_playerAngle < 0)
			_playerAngle += PI4;
		_playerDeltaX = cos(_playerAngle) * _velocity;
		_playerDeltaY = sin(_playerAngle) * _velocity;
	}
	if (key == 'd')
	{
		_playerAngle += 0.1;
		if (_playerAngle >  PI4)
			_playerAngle -= PI4;
		_playerDeltaX = cos(_playerAngle) * _velocity;
		_playerDeltaY = sin(_playerAngle) * _velocity;
	}
	if (key == 'w')
	{
		_playerPosX += _playerDeltaX;
		_playerPosY += _playerDeltaY;
	}
	if (key == 's')
	{
		_playerPosX -= _playerDeltaX;
		_playerPosY -= _playerDeltaY;
	}
	glutPostRedisplay();
}