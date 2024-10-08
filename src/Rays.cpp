#include "Rays.hpp"

Rays::Rays() {}

Rays::~Rays() {}

void Rays::drawRays(sf::RenderTarget &target, const Player &player, const Map &map)
{
	float angle = player.angle * PI / 180.0f;
	float aTan = -1.0f / tan(angle);
	// float nTan = -tan(angle);
	float cellSize = map.getCellSize();

	sf::Vector2f rayPos, offset;
	if (sin(angle) >= 0.001f)
	{
		rayPos.y = std::round(player.position.y / cellSize) * cellSize + cellSize;
		rayPos.x = (player.position.y - rayPos.y) * aTan + player.position.x;
		offset.y = cellSize;
		offset.x = -offset.y * aTan;
	}
	else if (sin(angle) <= -0.001f)
	{
		rayPos.y = std::round(player.position.y / cellSize) * cellSize;
		rayPos.x = (player.position.y - rayPos.y) * aTan + player.position.x;
		offset.y = -cellSize;
		offset.x = -offset.y * aTan;
	}
	else if(sin(angle) == 0 || sin(angle) == PI)
	{
		rayPos = player.position;
		return;
	}

	const auto &grid = map.getGrid();
	for (size_t i = 0; i < MAX_RAYS; i++)
	{
		int mapX = (int)(rayPos.x / cellSize);
		int mapY = (int)(rayPos.y / cellSize);

		if (mapY >= 0 && mapY < static_cast<int>(grid.size()) &&
			mapX >= 0 && mapX < static_cast<int>(grid[mapY].size()) &&
			grid[mapY][mapX])
		{
			break;
		}

		rayPos += offset;
	}


	sf::Vertex line[] = {
		sf::Vertex(player.position),
		sf::Vertex(rayPos)};
	line->color = sf::Color::Red;
	target.draw(line, 2, sf::Lines);
}