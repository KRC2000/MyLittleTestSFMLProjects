#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

	const int mapWidth = 500;
	const int mapHeight = 500;
	const float tileSize_px = 5;

	int tilMapData_arr[mapHeight][mapWidth];

	RectangleShape stamp({ tileSize_px, tileSize_px });
	RenderTexture render_t;
	Texture tile0_t, tile1_t;
int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(800, 600), "SFML works!");


	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			tilMapData_arr[i][k] = rand() % 2;
		}
	}

	Texture tile0_t, tile1_t;

	tile0_t.loadFromFile("t_0.png");
	tile1_t.loadFromFile("t_1.png");

	RectangleShape stamp({ tileSize, tileSize });
	RenderTexture render_t;

	render_t.create(mapWidth * tileSize, mapHeight * tileSize);

	render_t.create(mapWidth * tileSize_px, mapHeight * tileSize_px);




	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			if (tilMapData_arr[i][k] == 0)
			{
				stamp.setTexture(&tile0_t);
			}
			if (tilMapData_arr[i][k] == 1)
			{
				stamp.setTexture(&tile1_t);
			}
			stamp.setPosition({k * tileSize_px, i * tileSize_px });
			render_t.draw(stamp);

			cout << tilMapData_arr[i][k];
		}
		cout << endl;
	}

	render_t.display();

	Sprite render_t_s;
	render_t_s.setTexture(render_t.getTexture());

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();

		window.draw(render_t_s);

		window.display();
	}

	return 0;
};


void draw()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			if (tilMapData_arr[i][k] == 0)
			{
				stamp.setTexture(&tile0_t);
			}
			if (tilMapData_arr[i][k] == 1)
			{
				stamp.setTexture(&tile1_t);
			}
			stamp.setPosition({ k * tileSize_px, i * tileSize_px });
			render_t.draw(stamp);

		}
	}
}