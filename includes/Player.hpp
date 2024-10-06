#pragma once

#include "Utils.hpp"

class Player
{
private:
	float	_playerPosX;
	float	_playerPosY;
	float	_playerDeltaX;
	float	_playerDeltaY;
	float	_playerAngle;
	float	_velocity;
public:
	Player();
	Player(Player const &obj);
	Player &operator=(Player const &obj);
	~Player();

    // Getters
    float getPlayerPosX() const;
    float getPlayerPosY() const;
    float getPlayerDeltaX() const;
    float getPlayerDeltaY() const;
    float getPlayerAngle() const;
    float getVelocity() const;

    // Setters
    void setPlayerPosX(float posX);
    void setPlayerPosY(float posY);
    void setPlayerDeltaX(float deltaX);
    void setPlayerDeltaY(float deltaY);
    void setPlayerAngle(float angle);
    void setVelocity(float velocity);

	void drawPlayer();
	void playerMovement(unsigned char key, int x, int y);
};