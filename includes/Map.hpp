#pragma once

#include "Utils.hpp"

class Map
{
private:
	int					_mapWidth;
	int					_mapHeight;
	int					_mapSize;
public:
	std::vector<int>	_map;
	Map();
	~Map();

    // Getters
    int getMapWidth() const;
    int getMapHeight() const;
    int getMapSize() const;

    // Setters
    void setMapWidth(int width);
    void setMapHeight(int height);
    void setMapSize(int size);

	void	drawMap2D();
};