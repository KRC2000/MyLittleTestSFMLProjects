#pragma once
#include "Scene.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene(String sceneName, RenderWindow& window, const Time& gTime, const Time& dTime) : Scene(sceneName, window, gTime, dTime) {};
	virtual String update() { return "false"; };
	virtual void processInputEvents(Event& event);
	virtual void draw(RenderTarget& target, RenderStates states) const {};
};

