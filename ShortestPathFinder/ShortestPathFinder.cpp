#include <SFML/Graphics.hpp>
#include <iostream>

#include "Pathfinder.h"

using namespace sf;
using namespace std;
using v2i = Vector2i;


int main()
{

	finder::Pathfinder p;

	v2i mSize = {10, 10};
	vector<Uint8> map
	{
		3, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 1, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 0, 1, 2, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	p.setUp(map, mSize);

	vector<Vector2i> vec = p.computePath();

	for (auto& v : vec)
		cout << v.x << "; " << v.y << endl;



	srand(time(NULL));
	RenderWindow window(VideoMode(800, 600), "SFML works!");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		p.debugDraw(window, 30);

		window.display();
	}

	return 0;
}

