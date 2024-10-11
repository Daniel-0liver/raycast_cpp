#pragma once

#include "Utils.hpp"

class Map
{
private:
	float	_cellSize;
	std::vector<std::vector<int>> _grid;
public:
	Map(float cellSize, int width, int height);
	Map(float cellSize, std::vector<std::vector<int>> grid);
	Map(Map const &obj);
	Map &operator=(Map const &obj);
	~Map();

	void drawMinimap(sf::RenderTarget &target, float cellSize);
	const std::vector<std::vector<int>> &getGrid() const;
	float getCellSize() const;
	void setCellSize(float cellSize);
};