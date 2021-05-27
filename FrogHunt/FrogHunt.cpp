#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Utility.h"
#include "GlobalVars.h"

#include "Frog.h"
#include "Fly.h"
#include "Level.h"

using namespace std;
using namespace sf;



Vector2f mousePos;

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(SCR_SIZE.x, SCR_SIZE.y), "SFML works!");

	/*
	Frog textures in vec:
	0 - frog
	1 - tongue
	*/
	int FROG_T_AMOUNT = 2;
	vector<Texture> frog_tVec; 
	Utility::fillVector<Texture>(frog_tVec, FROG_T_AMOUNT);

	frog_tVec[0].loadFromFile("frog1.png");			frog_tVec[0].setSmooth(true);
	frog_tVec[1].loadFromFile("tongue1.png");		frog_tVec[1].setSmooth(true);	frog_tVec[1].setRepeated(true);
	
	Texture leaf_t, fly_t;
	leaf_t.loadFromFile("leaf1.png");
	leaf_t.setSmooth(true);

	fly_t.loadFromFile("fly.png");
	fly_t.setSmooth(true);

	Frog frog(frog_tVec);


	Sprite leaf_s(leaf_t);
	leaf_s.setOrigin(leaf_s.getGlobalBounds().width / 2, leaf_s.getGlobalBounds().height / 2);
	leaf_s.setPosition(SCR_SIZE.x/2, SCR_SIZE.y/2);
	leaf_s.setScale(0.7f, 0.7f);


	vector<Fly> flyVec;
	Level lvl1(flyVec, fly_t);

	Clock globalTimer;
	Clock deltaTimer;

	while (window.isOpen())
	{
		float deltaTime = deltaTimer.getElapsedTime().asSeconds();
		deltaTimer.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					frog.fire();
				}
			}
		}


		mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		lvl1.update();


		frog.update(mousePos, deltaTime, globalTimer.getElapsedTime().asSeconds());

		for (int i = 0; i < flyVec.size(); i++)
		{
			flyVec[i].update(deltaTime, globalTimer.getElapsedTime().asSeconds(), frog.getTongueHeadPos());
			
			if (frog.getState() == Frog::FIRED)
			{
				if (frog.getTongueHeadRect().intersects(flyVec[i].getRect()))
				{
					flyVec[i].setStateGrabbed();
					frog.setStateRetrieve();
				}
			}

			if (flyVec[i].getState() == Fly::GRABBED)
			{
				if (frog.getState() == Frog::IDLE)
				{
					flyVec.erase(flyVec.begin() + i);
					frog.playEatAnim(globalTimer.getElapsedTime().asSeconds());
				}
			}
		}
		

		window.clear(Color::Cyan);

		window.draw(leaf_s);
		window.draw(frog);
		for (auto& fly : flyVec)
			window.draw(fly);

		window.display();
	}

	return 0;
};
