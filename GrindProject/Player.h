#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d.h>

using namespace sf;
using namespace std;

class Player :
	public Drawable
{
	b2CircleShape shape;
	b2BodyDef bdef;
	b2Body* body = nullptr;

	string name = "player";
	bool canJump = false;

	const Time* gTime;

	Time jumpStartTimestamp = Time::Zero;

public:
	RectangleShape rect{ {32, 32} };

	Player(b2World& world, const Time& globalTime);


	void update()
	{
		canJump = false;
		if (body->GetContactList())
		{
			for (b2ContactEdge* contactEdge = body->GetContactList(); contactEdge != nullptr; contactEdge = contactEdge->next)
			{
				if (contactEdge->contact->IsTouching())
				{
					if(body->GetLinearVelocity().y > -5) canJump = true;
				}
			}
		}

		
	};

	void updateInPhysicsCycle()
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (body->GetLinearVelocity().x > -5)
				body->ApplyForceToCenter({ -110.f, 0 }, true);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (body->GetLinearVelocity().x < 5)
				body->ApplyForceToCenter({ 110.f, 0 }, true);
		}


		if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
		{
			if (body->GetContactList())
			{
				for (b2ContactEdge* contactEdge = body->GetContactList(); contactEdge != nullptr; contactEdge = contactEdge->next)
				{
					if (contactEdge->contact->IsTouching())
					{
						body->SetLinearVelocity({ body->GetLinearVelocity().x - body->GetLinearVelocity().x / 10, body->GetLinearVelocity().y });
					}
				}
			}
		}
		
	
	}

	void processInputEvents(Event& event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Space)
			{
				if (canJump)
				{
					jump();
				}
			}
		}


	};

	virtual void draw(RenderTarget& target, RenderStates states) const 
	{
		target.draw(rect);
	};

private:

	void jump();

};

