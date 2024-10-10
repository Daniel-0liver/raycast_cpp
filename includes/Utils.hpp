#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <limits>
#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Rays.hpp"

const float PI = 3.1415926535f;
const float TURN_SPEED = 100.0f;
const float MOVE_SPEED = 100.0f;
const float PLAYER_FOV = 60.0f;
const float WINDOW_WIDTH = 1200.0f;
const float WINDOW_HEIGHT = 675.0f;
const float PLAYER_X = 128.0f;
const float PLAYER_Y = 128.0f;
const float TILE_SIZE = 48.0f;
const int	MAX_RAYS = 600.0f;
const float MAX_RAYCAST_DEPTH = 16.0f;
const float COLUMN_WIDTH = WINDOW_WIDTH / MAX_RAYS;

std::vector<std::vector<int>> parseMap(std::string filename);