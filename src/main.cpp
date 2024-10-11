#include "Utils.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycast",
							sf::Style::Close | sf::Style::Titlebar);

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

	Rays rays;

	sf::Clock gameClock;
	sf::Text fps;
	sf::Font font;
	font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");
	fps.setFont(font);
	fps.setCharacterSize(24);
	fps.setFillColor(sf::Color::Red);
	fps.setPosition(WINDOW_WIDTH - 164, 0);

	while (window.isOpen())
	{
		float deltaTime = gameClock.restart().asSeconds();
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		player.update(deltaTime);
		fps.setString("FPS: " + std::to_string(1.0f / deltaTime));

		window.clear();
		rays.drawRays3D(window, player, map);
		map.drawMinimap(window, TILE_SIZE * MINIMAP_SCALE);
		rays.drawRays2D(window, player, map);
		window.draw(fps);
		window.display();
	}

	return (0);
}