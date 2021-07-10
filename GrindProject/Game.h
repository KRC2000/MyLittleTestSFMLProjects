#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "MainMenuScene.h"
#include "GameScene.h"


using namespace sf;

using v2f = Vector2f;
using v2i = Vector2i;
using v2u = Vector2u;

class Game
{
	const v2u SCR_SIZE = { 800, 600 };
	RenderWindow window{ {SCR_SIZE.x, SCR_SIZE.y}, "Window"};

	Time globalTime, deltaTime;

	std::vector<Scene*> sceneVec;
	MainMenuScene mainMenuScene{ "mainMenuScene", window, globalTime, deltaTime };
	GameScene gameScene{ "gameScene", window, globalTime, deltaTime };


	Event event;
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