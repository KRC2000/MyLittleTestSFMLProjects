#pragma once
#include <box2d.h>

#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"

using v2f = Vector2f;
using v2i = Vector2i;

class GameScene : public Scene
{
	b2Vec2 gravity{ 0.0f, 10.0f };
	b2World world{ gravity };
	Camera cam {*window};
	Map map1{ "Map/tileMap1.tmx", "map1", world};

	Clock physicsCycleTimer;

	String s = "box";

	Player p1{world, *gTime};

public:
	GameScene(String sceneName, RenderWindow& window, const Time& gTime, const Time& dTime);
	virtual String update() ;
	virtual void processInputEvents(Event& event);
	virtual void draw(RenderTarget& target, RenderStates states) const ;
};

