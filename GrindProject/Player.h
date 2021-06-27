#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d.h>

using namespace sf;
using namespace std;

class Player :
	public Drawable
{
	b2PolygonShape shape;
	b2BodyDef bdef;
	b2Body* body = nullptr;

	string name = "player";


public:
	RectangleShape rect{ {32, 32} };

	Player(b2World& world) 
	{
		rect.setOrigin(32 / 2, 32 / 2);

		float scale = 32;

		shape.SetAsBox(16/scale, 16/scale);

		bdef.type = b2_dynamicBody;
		bdef.userData.pointer = (uintptr_t)&name;
		bdef.position.Set(32/scale, 32/scale);

		body = world.CreateBody(&bdef);
		body->CreateFixture(&shape, 2);

		body->GetFixtureList()->SetFriction(1);
		body->SetFixedRotation(true);
	};

	void update()
	{
		
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
		
	
	}

	void processInputEvents(Event& event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Space)
			{
				body->ApplyLinearImpulseToCenter({ 0, -10.f }, true);
			}
		}


	};

	virtual void draw(RenderTarget& target, RenderStates states) const 
	{
		target.draw(rect);
	};

};

