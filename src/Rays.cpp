#include "Rays.hpp"

Rays::Rays() {}

Rays::~Rays() {}

void Rays::drawRays(sf::RenderTarget &target, const Player &player, const Map &map)
{
	float angle = player.angle * PI / 180.0f;
	float horTan = -1.0f / tan(angle);
	float verTan = -tan(angle);
	float cellSize = map.getCellSize();

	sf::Vector2f vRayPos, hRayPos, offset;
	size_t vdof = 0, hdof = 0;
	float vDist = std::numeric_limits<float>::max();
	float hDist = std::numeric_limits<float>::max();

	// Vertical ray
	if (cos(angle) > 0.001f)
	{
		vRayPos.x = std::floor(player.position.x / cellSize) * cellSize + cellSize;
		vRayPos.y = (player.position.x - vRayPos.x) * verTan + player.position.y;
		offset.x = cellSize;
		offset.y = -offset.x * verTan;
	}
	else if (cos(angle) < -0.001f)
	{
		vRayPos.x = std::floor(player.position.x / cellSize) * cellSize - 0.0001f;
		vRayPos.y = (player.position.x - vRayPos.x) * verTan + player.position.y;
		offset.x = -cellSize;
		offset.y = -offset.x * verTan;
	}
	else
	{
		vdof = MAX_RAYS;
	}

	const auto &grid = map.getGrid();
	for (; vdof < MAX_RAYS; vdof++)
	{
		int mapX = (int)(vRayPos.x / cellSize);
		int mapY = (int)(vRayPos.y / cellSize);

		if (mapY >= 0 && mapY < static_cast<int>(grid.size()) &&
			mapX >= 0 && mapX < static_cast<int>(grid[mapY].size()) &&
			grid[mapY][mapX])
		{
			vDist = sqrt(pow(player.position.x - vRayPos.x, 2) + pow(player.position.y - vRayPos.y, 2));
			break;
		}

		vRayPos += offset;
	}

	//Horizontal ray
	if (sin(angle) > 0.001f)
	{
		hRayPos.y = std::floor(player.position.y / cellSize) * cellSize + cellSize;
		hRayPos.x = (player.position.y - hRayPos.y) * horTan + player.position.x;
		offset.y = cellSize;
		offset.x = -offset.y * horTan;
	}
	else if (sin(angle) < -0.001f)
	{
		hRayPos.y = std::floor(player.position.y / cellSize) * cellSize - 0.0001f;
		hRayPos.x = (player.position.y - hRayPos.y) * horTan + player.position.x;
		offset.y = -cellSize;
		offset.x = -offset.y * horTan;
	}
	else
	{
		hdof = MAX_RAYS;
	}

	for (; hdof < MAX_RAYS; hdof++)
	{
		int mapX = (int)(hRayPos.x / cellSize);
		int mapY = (int)(hRayPos.y / cellSize);

		if (mapY >= 0 && mapY < static_cast<int>(grid.size()) &&
			mapX >= 0 && mapX < static_cast<int>(grid[mapY].size()) &&
			grid[mapY][mapX])
		{
			hDist = sqrt(pow(player.position.x - hRayPos.x, 2) + pow(player.position.y - hRayPos.y, 2));
			break;
		}

		hRayPos += offset;
	}

	sf::Vertex line[] = {
		sf::Vertex(player.position),
		sf::Vertex(vDist < hDist ? vRayPos : hRayPos)};
	line->color = sf::Color::Red;
	target.draw(line, 2, sf::Lines);
}