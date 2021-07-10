#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	sceneVec.push_back(&mainMenuScene);
	sceneVec.push_back(&gameScene);


}

void Game::process()
{
	while (window.isOpen())
	{
		deltaTime = deltaTimer.restart();
		globalTime = globalTimer.getElapsedTime();

		inputReg();

		// Updating all scenes
		for ( auto& scene : sceneVec)
			scene->update();

		window.clear();

		// Drawing all scenes
		for (auto& scene : sceneVec)
			window.draw(*scene);

		window.display();

	}
}

void Game::inputReg()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		
		for (auto& scene : sceneVec)
			scene->processInputEvents(event);
	}
}
