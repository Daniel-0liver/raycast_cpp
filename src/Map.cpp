#include "Map.hpp"

Map::Map() : _mapWidth(8), _mapHeight(8), _mapSize(64), _map{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1
} {}

Map::~Map() {}

// Getters
int Map::getMapWidth() const {
    return _mapWidth;
}

int Map::getMapHeight() const {
    return _mapHeight;
}

int Map::getMapSize() const {
    return _mapSize;
}

// Setters
void Map::setMapWidth(int width) {
    _mapWidth = width;
}

void Map::setMapHeight(int height) {
    _mapHeight = height;
}

void Map::setMapSize(int size) {
    _mapSize = size;
}

void Map::drawMap2D() {
	int x, y, xOffSet, yOffSet;

    for (y = 0; y < _mapHeight; y++) {
        for (x = 0; x < _mapWidth; x++) {
            if (_map[y * _mapWidth + x] == 1)
			{
                glColor3f(1.0, 1.0, 1.0);
			}
			else
				glColor3f(0, 0, 0);

			xOffSet = x * _mapSize;
			yOffSet = y * _mapSize;
			glBegin(GL_QUADS);
			glVertex2i(0 + xOffSet + 1, 0 + yOffSet + 1);
			glVertex2i(0 + xOffSet + 1, yOffSet + _mapSize -1);
			glVertex2i(xOffSet + _mapSize -1, yOffSet + _mapSize -1);
			glVertex2i(xOffSet + _mapSize -1, 0 + yOffSet + 1);
			glEnd();
        }
    }
}