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
	sf::Vector2u vMapPosition, hMapPosition;
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
		vdof = MAX_RAYCAST_DEPTH;
	}

	const auto &grid = map.getGrid();
	for (; vdof < MAX_RAYCAST_DEPTH; vdof++)
	{
		int mapX = (int)(vRayPos.x / cellSize);
		int mapY = (int)(vRayPos.y / cellSize);

		if (mapY >= 0 && mapY < static_cast<int>(grid.size()) &&
			mapX >= 0 && mapX < static_cast<int>(grid[mapY].size()) &&
			grid[mapY][mapX])
		{
			isHit = true;
			vMapPosition = sf::Vector2u(mapX, mapY);
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
		hdof = MAX_RAYCAST_DEPTH;
	}

	for (; hdof < MAX_RAYCAST_DEPTH; hdof++)
	{
		int mapX = (int)(hRayPos.x / cellSize);
		int mapY = (int)(hRayPos.y / cellSize);

		if (mapY >= 0 && mapY < static_cast<int>(grid.size()) &&
			mapX >= 0 && mapX < static_cast<int>(grid[mapY].size()) &&
			grid[mapY][mapX])
		{
			isHit = true;
			hMapPosition = sf::Vector2u(mapX, mapY);
			hDist = sqrt(pow(start.x - hRayPos.x, 2) + pow(start.y - hRayPos.y, 2));
			break;
		}

		hRayPos += offset;
	}

	return (vDist < hDist) ? Ray{vMapPosition, vRayPos, vDist, isHit, vDist < hDist} 
			: Ray{hMapPosition, hRayPos, hDist, isHit, vDist < hDist};
}

void Rays::drawRays2D(sf::RenderTarget &target, const Player &player, const Map &map)
{
	for (float angle = player.angle - 30.0f / 2.0f;
		 angle < player.angle + 30.0f / 2.0f;
		 angle += 0.1f)
	{
		sf::Vector2f tempPlayerPositon = player.position;
		tempPlayerPositon.x = player.position.x * MINIMAP_SCALE;
		tempPlayerPositon.y = player.position.y * MINIMAP_SCALE;

		Map tempMap = map;
		tempMap.setCellSize(map.getCellSize() * MINIMAP_SCALE);
		Ray ray = castRay(tempPlayerPositon, tempMap, angle);
		if (ray.isHit)
		{
			sf::Vertex line[] = {
				sf::Vertex(tempPlayerPositon),
				sf::Vertex(ray.hitPosition)};
			target.draw(line, 2, sf::Lines);
		}
	}
}

void Rays::drawRays3D(sf::RenderTarget &target, const Player &player, const Map &map)
{
	sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f));
	background.setFillColor(sf::Color(100, 170, 250, 128));
	target.draw(background);

	background.setPosition(0.0f, WINDOW_HEIGHT / 2.0f);
	background.setFillColor(sf::Color(70, 70, 70, 128));
	target.draw(background);

	float angle = player.angle - PLAYER_FOV / 2.0f;
	float angleStep = PLAYER_FOV / MAX_RAYS;
	const float maxRaycastDepth = MAX_RAYCAST_DEPTH * map.getCellSize();
	for(size_t i = 0; i < MAX_RAYS; i++, angle += angleStep)
	{
		Ray ray = castRay(player.position, map, angle);
		if (ray.isHit)
		{
			ray.distance *= cos((angle - player.angle) * PI / 180.0f);

			float wallHeight = (map.getCellSize() * WINDOW_HEIGHT) / ray.distance;
			if(wallHeight > WINDOW_HEIGHT)
				wallHeight = WINDOW_HEIGHT;

			float brightness = 1.0f - (ray.distance / maxRaycastDepth);
			if(brightness < 0.0f)
				brightness = 0.0f;
			
			float shade = (ray.isHitVertical ? 0.8f : 1.0f) * brightness;

			float wallOffset = (WINDOW_HEIGHT - wallHeight) / 2.0f;
			sf::RectangleShape column(sf::Vector2f(COLUMN_WIDTH, wallHeight));
			column.setPosition(i * COLUMN_WIDTH, wallOffset);
			if(map.getGrid()[ray.mapPosition.y][ray.mapPosition.x] == 32)
				column.setFillColor(sf::Color(255 * shade, 100 * shade, 0 * shade));
			else if(map.getGrid()[ray.mapPosition.y][ray.mapPosition.x] == 1)
				column.setFillColor(sf::Color(255 * shade, 255 * shade, 255 * shade));
			else if(map.getGrid()[ray.mapPosition.y][ray.mapPosition.x] == 2)
				column.setFillColor(sf::Color(100, 100, 100));
			target.draw(column);
		}
	}
}