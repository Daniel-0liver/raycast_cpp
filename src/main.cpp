#include "Utils.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycast");

	if (!window.isOpen())
		return (1);
	std::vector<std::vector<int>> grid = parseMap("assets/maps/map.txt");
	if (grid.empty())
	{
		std::cerr << "Error while parsing map" << std::endl;
		return (1);
	}

	Map map(TILE_SIZE, grid);

	Player player(sf::Vector2f(PLAYER_X, PLAYER_Y));

	sf::Clock gameClock;

	while (window.isOpen())
	{
		float deltaTime = gameClock.restart().asSeconds();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.update(deltaTime);

		window.clear();
		map.draw(window);
		player.draw(window);
		window.display();
	}

	return (0);
}