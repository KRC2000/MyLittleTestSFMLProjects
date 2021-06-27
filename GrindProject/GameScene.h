#pragma once
#include "Scene.h"

#include "Map.h"

class GameScene : public Scene
{
	Map map1{ "Map/tileMap1.tmx", "map1" };
public:
	GameScene(String sceneName);
	virtual String update(RenderTarget& target, Event& event, Time gTime, Time dTime) {return "false";};
	virtual void draw(RenderTarget& target, RenderStates states) const {};
};

