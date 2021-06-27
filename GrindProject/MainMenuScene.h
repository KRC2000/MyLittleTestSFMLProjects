#pragma once
#include "Scene.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene(String sceneName) : Scene(sceneName) {};
	virtual String update(RenderTarget& target, Event& event, Time gTime, Time dTime) { return "false"; };
	virtual void draw(RenderTarget& target, RenderStates states) const {};
};

