#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

struct Button
{
	RectangleShape rect;

	Button() { rect.setSize({ 25, 25 }); rect.setFillColor(Color::Blue); };
	void update(Vector2f mousePos) { if (rect.getGlobalBounds().contains(mousePos)) rect.setFillColor(Color::Red); else rect.setFillColor(Color::Green); };
};

int main()
{
	RenderWindow window(VideoMode(800, 800), "SFML works!");

	View view({ 200, 250 }, { 400, 500 });
	//window.setView(view);

	Button b;
	b.rect.setPosition(50, 0);

	//Sprite rtHolder, rt1_s;
	RectangleShape rtHolder, rt1_s;
	RenderTexture rt, rt1;
	View v({ 250, 500 }, { 500, 1000 });
	rt.create(1000, 1000);
	rt.clear(Color::Cyan);
	rt.setView(v);
	rtHolder.setSize({ 500, 1000 });

	View v1({50, 50}, {100, 100});
	rt1.create(1000, 1000);
	rt1.setView(v1);
	rt1.clear(Color::Red);
	rt1.draw(b.rect);
	rt1.display();

	rt1_s.setSize(v1.getSize());
	rt1_s.setTexture(&rt1.getTexture());
	rt1_s.move(50, 45);
	
	rt.draw(rt1_s);
	rt.display();
	rtHolder.setTexture(&rt.getTexture());
	rtHolder.setPosition(150, 300);


	while (window.isOpen())
	{

		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		//Vector2f mousePos = rt.mapPixelToCoords(Mouse::getPosition(window));
		//Vector2f mousePos = (Vector2f)Mouse::getPosition(window);

		// Размер текстуры 1000х1000
		// Размер rectangle-а 500х300
		// Размер камеры
		// 1 - 1000x1000
		// 2 - 1020x1000
		// 3 - 1100x1000
		// 4 - 500x1000
		// Размер rectangle-а 320х100
		// 5 - 1000x1000
		// 6 - 1020x1000
		// 7 - 1100x1000
		// 8 - 500x1000

		mousePos -= rtHolder.getPosition();
		Vector2i v = rt.mapCoordsToPixel(mousePos);
		cout << v.x << "    " << v.y << endl;

		//mousePos = rt.mapPixelToCoords()

		mousePos -= rtHolder.getPosition();
		mousePos = rt.mapPixelToCoords((Vector2i)mousePos);
		//cout << mousePos.x << "    " << mousePos.y << endl;
		// 1 - { 500, 300 }
		// 2 - { 510, 300 }
		// 3 - { 550, 300 }
		// 4 - { 250, 300 }
		//
		// 5 - { 320, 100 }
		// 6 - { 325, 100 }
		// 7 - { 350, 100 }
		// 8 - { 160, 100 }

		mousePos = { mousePos.x * 2, mousePos.y * 2 };
		//cout << mousePos.x << "    " << mousePos.y << endl;
		// 1 - { 1000, 600 }
		// 2 - { 1020, 600 }
		// 3 - { 1100, 600 }
		// 4 - { 500, 600 }

		//Vector2f c = { rtHolder.getSize().x / rt.getView().getSize().x, rtHolder.getSize().y / rt.getView().getSize().y};
		// 1 - { 500 / 1000, 300 / 1000} = { 0.5, 0.3}
		// 2 - { 500 / 1020, 300 / 1000} = { 0.49, 0.3}
		// 3 - { 500 / 1100, 300 / 1000} = { 0.45, 0.3}
		// 4 - { 500 / 500, 300 / 1000} = { 1, 0.3}

		//mousePos = { mousePos.x / c.x, mousePos.y / c.y };
		// 1 - { 1000, 1000 }
		// 2 - { 1040, 1000 }
		// 3 - { 1200, 1000 }
		// 4 - { 250, 1000 }


		//mousePos = rt.mapPixelToCoords((Vector2i)mousePos);
		// 
		//mousePos = (Vector2f)rt.mapCoordsToPixel(mousePos);
		//mousePos = rt.mapCoordsToPixel(Mouse::getPosition(window));
		//mousePos = window.mapPixelToCoords((Vector2i)mousePos, v);
		//mousePos = window.mapPixelToCoords((Vector2i)mousePos, rt.getView());

		//cout << mousePos.x << "    "<< mousePos.y << endl;

		// Coords inside rt1
		//mousePos -= rt1_s.getPosition();
		//mousePos = rt1.mapPixelToCoords((Vector2i)mousePos);
		//cout << mousePos.x << "    " << mousePos.y << endl;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//b.update(mousePos);

		rt1.clear(Color::Red);
		rt1.draw(b.rect);
		rt1.display();

		rt.clear(Color::Cyan);
		rt.draw(rt1_s);
		rt.display();

		window.clear();

		window.draw(rtHolder);

		window.display();
	}

	return 0;
};


