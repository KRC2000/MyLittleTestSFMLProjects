#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	window.create(VideoMode(800, 600), "Build");

	sceneVec.push_back(&mainMenuScene);
	sceneVec.push_back(&gameScene);


}

void Game::process()
{
	while (window.isOpen())
	{


		inputReg();

		// Updating all scenes
		for ( auto& scene : sceneVec)
			scene->update(window, event, globalTimer.getElapsedTime(), deltaTimer.getElapsedTime());

		// Drawing all scenes
		for (auto& scene : sceneVec)
			window.draw(*scene);



		deltaTimer.restart();
	}
}

void Game::inputReg()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == Event::KeyPressed)
		{
		}
	}
}
