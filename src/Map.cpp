#include "Map.hpp"

Map::Map(float cellSize, int width, int height) : _cellSize(cellSize), _grid(height, std::vector<int>(width, 1)) {}

Map::Map(float cellSize, std::vector<std::vector<int>> grid) : _cellSize(cellSize), _grid(grid) {}

Map::~Map() {}

void Map::draw(sf::RenderTarget &target)
{
	if (_grid.empty())
		return;
	sf::RectangleShape backGround(sf::Vector2f((float)_grid[0].size() * _cellSize, (float)_grid.size() * _cellSize));

	backGround.setFillColor(sf::Color::Black);

	target.draw(backGround);

	sf::RectangleShape cell(sf::Vector2f(_cellSize * 0.95f, _cellSize * 0.95f));

	for (size_t y = 0; y < _grid.size(); y++)
	{
		for (size_t x = 0; x < _grid[y].size(); x++)
		{
			if (_grid[y][x] == 0)
			{
				cell.setFillColor(sf::Color(128, 128, 128));
			}
			else if (_grid[y][x] == 1)
			{
				cell.setFillColor(sf::Color::White);
			}
			else
			{
				cell.setFillColor(sf::Color::Black);
			}

			cell.setPosition((float)x * _cellSize + _cellSize * 0.025f, (float)y * _cellSize + _cellSize * 0.025f);
			target.draw(cell);
		}
	}
}

const std::vector<std::vector<int>> &Map::getGrid() const
{
	return (_grid);
}

float Map::getCellSize() const
{
	return (_cellSize);
}