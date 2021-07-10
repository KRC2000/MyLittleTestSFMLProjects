#include "GameScene.h"

GameScene::GameScene(String sceneName, RenderWindow& window, const Time& gTime, const Time& dTime) :Scene(sceneName, window, gTime, dTime)
{
	cam.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));

}

String GameScene::update()
{
	if (physicsCycleTimer.getElapsedTime().asSeconds() > 1 / 60.f)
	{
		world.Step(1 / 60.f, 8, 3);
		p1.updateInPhysicsCycle();
		
		physicsCycleTimer.restart();
	}
	

	for (auto* body = world.GetBodyList(); body != nullptr; body = body->GetNext())
	{
		uintptr_t uDataptr = body->GetUserData().pointer;
		if (uDataptr != 0)
		{
			string name = *reinterpret_cast<string*>(uDataptr);
			if (name == "player")
			{
				p1.rect.setPosition(body->GetPosition().x*32, body->GetPosition().y*32);
				p1.rect.setRotation(body->GetAngle() * (180 / 3.14));
			}
		}
	}


	p1.update();	
	cam.update(p1.rect.getPosition());

	return "false";
}

void GameScene::processInputEvents(Event& event)
{
	window->setKeyRepeatEnabled(false);
	if (event.type == Event::Resized)
	{
		cam.setSize((v2f)window->getSize());
	}


	p1.processInputEvents(event);
	cam.processInputEvents(event);
}

void GameScene::draw(RenderTarget& target, RenderStates states) const
{
	target.setView(cam);

	target.draw(map1);
	target.draw(p1);
}

