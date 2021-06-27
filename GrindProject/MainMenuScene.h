#pragma once
#include "Scene.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene(String sceneName, RenderWindow& window) : Scene(sceneName, window) {};
	virtual String update(Time gTime, Time dTime) { return "false"; };
	virtual void processInputEvents(Event& event);
	virtual void draw(RenderTarget& target, RenderStates states) const {};
};

