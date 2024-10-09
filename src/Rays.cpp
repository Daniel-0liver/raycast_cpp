#include "Rays.hpp"

Rays::Rays() {}

Rays::~Rays() {}

Ray Rays::castRay(sf::Vector2f start, const Map &map, float angleInDegrees)
{
	float angle = angleInDegrees * PI / 180.0f;
	float horTan = -1.0f / tan(angle);
	float verTan = -tan(angle);
	float cellSize = map.getCellSize();

	bool isHit = false;
	sf::Vector2f vRayPos, hRayPos, offset;
	size_t vdof = 0, hdof = 0;
	float vDist = std::numeric_limits<float>::max();
	float hDist = std::numeric_limits<float>::max();

	// Vertical ray
	if (cos(angle) > 0.001f)
	{
		vRayPos.x = std::floor(start.x / cellSize) * cellSize + cellSize;
		vRayPos.y = (start.x - vRayPos.x) * verTan + start.y;
		offset.x = cellSize;
		offset.y = -offset.x * verTan;
	}
	else if (cos(angle) < -0.001f)
	{
		vRayPos.x = std::floor(start.x / cellSize) * cellSize - 0.0001f;
		vRayPos.y = (start.x - vRayPos.x) * verTan + start.y;
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
			isHit = true;
			vDist = sqrt(pow(start.x - vRayPos.x, 2) + pow(start.y - vRayPos.y, 2));
			break;
		}

		vRayPos += offset;
	}

	// Horizontal ray
	if (sin(angle) > 0.001f)
	{
		hRayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
		hRayPos.x = (start.y - hRayPos.y) * horTan + start.x;
		offset.y = cellSize;
		offset.x = -offset.y * horTan;
	}
	else if (sin(angle) < -0.001f)
	{
		hRayPos.y = std::floor(start.y / cellSize) * cellSize - 0.0001f;
		hRayPos.x = (start.y - hRayPos.y) * horTan + start.x;
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
			isHit = true;
			hDist = sqrt(pow(start.x - hRayPos.x, 2) + pow(start.y - hRayPos.y, 2));
			break;
		}

		hRayPos += offset;
	}

	return (vDist < hDist) ? Ray{vRayPos, vDist, isHit} : Ray{hRayPos, hDist, isHit};
}

void Rays::drawRays(sf::RenderTarget &target, const Player &player, const Map &map)
{
	for (float angle = player.angle - PLAYER_FOV / 2.0f;
		 angle < player.angle + PLAYER_FOV / 2.0f;
		 angle += 0.1f)
	{
		Ray ray = castRay(player.position, map, angle);
		if (ray.isHit)
		{
			sf::Vertex line[] = {
				sf::Vertex(player.position),
				sf::Vertex(ray.hitPosition)};
			// line->color = sf::Color::Red;
			target.draw(line, 2, sf::Lines);
		}
	}
}