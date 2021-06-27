#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "MainMenuScene.h"
#include "GameScene.h"


using namespace sf;

using v2f = Vector2f;

class Game
{
	const v2f SCR_SIZE = { 800, 600 };

	std::vector<Scene*> sceneVec;
	MainMenuScene mainMenuScene{"mainMenuScene"};
	GameScene gameScene{ "gameScene" };


	Event event;
	RenderWindow window;
	Clock globalTimer, deltaTimer;
public:
	Game();
	virtual ~Game() {};
	void process();
private:
	void inputReg();
};

/*
To add new scene you need to:
-Create new scene class inherited from class Scene
-Create new scene field in class Game
-Add new scene's address to vector of scene pointers in Game constructor
*/