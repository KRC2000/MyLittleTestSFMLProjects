#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;



int main()
{
	RenderWindow window(VideoMode(400, 400), "SFML works!");

	//View view({ 300, 400 }, { 400, 500 });
	//window.setView(view);

	Texture t; t.loadFromFile("picture.png");
	Sprite s(t), ss(t); ss.move(10, 200);

	View v; v.reset(FloatRect{0, 0, 50, 50});
	RenderTexture rt; rt.create(50, 50);
	rt.setView(v);
	Sprite rtHolder(rt.getTexture());
	//rtHolder.setTextureRect(IntRect{0, 0, 200, 200});

	rt.draw(s);
	//s.move(0, 50);
	//rt.draw(s);
	rt.display();

	while (window.isOpen())
	{
		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

		v.move(0, 0.05);
		rt.setView(v);
		rt.clear();
		rt.draw(s);
		rt.draw(ss);
		rt.display();



		/*rt.setView(v);
		rt.display();*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();

		window.draw(rtHolder);

		window.display();
	}

	return 0;
};


