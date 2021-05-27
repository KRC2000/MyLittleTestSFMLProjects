#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "Map.h"
#include "Player.h"

using namespace sf;
using namespace std;

Time cycleTime;
Clock cycleTimer;

const int mapWidth = 40;
const int mapHeight = 40;
const float cellSize = 15;

View camera({0, 0, 400, 300});
Vector2f mousePos;


int main()
{
	Texture player_t;
	vector<Texture> mapTextures;

	player_t.loadFromFile("player.png");

	for (int i = 0; i < (int)Map::MapTexturesEnum::AMOUNT;i++) mapTextures.push_back(Texture());
	mapTextures[(int)Map::MapTexturesEnum::GROUND].loadFromFile("ground.png");
	mapTextures[(int)Map::MapTexturesEnum::STONE].loadFromFile("stone.png");

	srand(time(NULL));
	RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	Map map(mapWidth, mapHeight, cellSize, mapTextures);
	Player player(player_t, cellSize);
	camera.setCenter(player.player_s.getPosition());


	while (window.isOpen())
	{
		mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		cycleTime = cycleTimer.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W) player.go(Player::Direction::UP, map.cells_vec);
				if (event.key.code == Keyboard::A) player.go(Player::Direction::LEFT, map.cells_vec);
				if (event.key.code == Keyboard::S) player.go(Player::Direction::DOWN, map.cells_vec);
				if (event.key.code == Keyboard::D) player.go(Player::Direction::RIGHT, map.cells_vec);
				camera.setCenter(player.player_s.getPosition());
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					map.deleteCell(player.dig(mousePos, map.cells_vec));
				}
			}
		}


		window.clear();
		window.setView(camera);

		window.draw(map);
		window.draw(player);

		window.display();
	}

	return 0;
};
