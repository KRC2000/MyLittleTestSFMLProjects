#pragma once
#include <SFML/Graphics.hpp>

#include "GlobalVars.h"

using namespace sf;
using namespace Utility;

class Fly: public Drawable
{
public:
	enum State { FREE, GRABBED };
private:
	Sprite fly_s;
	Vector2f lastPos{0, 0};

	State state = FREE;

	// Movement curve parameters
	float xParam1 = 1;
	float xParam2 = 300;
	float yParam1 = 1;
	float yParam2 = 300;

	float flyInTimeStamp = 0;
	float flyInTime = 5;
public:
	Fly()
	{};

	void init(Texture& fly_t)
	{
		fly_s.setTexture(fly_t);
		fly_s.setTextureRect(IntRect(0, 0, fly_s.getGlobalBounds().width, fly_s.getGlobalBounds().height));
		fly_s.setOrigin(fly_s.getGlobalBounds().width / 2, fly_s.getGlobalBounds().height / 2);
		fly_s.setScale(0.1f, 0.1f);
	};

	void update(float deltaTime, float globalTime, Vector2f frogTongueHeadPos)
	{
		if (state == FREE)
		{
			if (flyInTimeStamp == 0) flyInTimeStamp = globalTime;
			float flyInFactor = flyInTime / (globalTime - flyInTimeStamp);

			float x, y;
			if (globalTime - flyInTimeStamp < flyInTime)
			{
				x = globVar::SCR_SIZE.x / 2 + cos(globalTime * xParam1) * (xParam2 * flyInFactor);
				y = globVar::SCR_SIZE.y / 2 + sin(globalTime * yParam1) * (yParam2 * flyInFactor);
			}
			else
			{
				x = globVar::SCR_SIZE.x / 2 + cos(globalTime * xParam1) * xParam2;
				y = globVar::SCR_SIZE.y / 2 + sin(globalTime * yParam1) * yParam2;
			}

			fly_s.setPosition(x, y);


			Vector2f motionVec = fly_s.getPosition() - lastPos;
			normiliseVec(motionVec.x, motionVec.y);
			float angle = getAngleNormVec(motionVec.x, motionVec.y);

			if (motionVec.y < 0) angle = -angle;
			fly_s.setRotation(angle);

			lastPos = fly_s.getPosition();
		}
		if (state == GRABBED)
		{
			fly_s.setPosition(frogTongueHeadPos);
		}
	};

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(fly_s);
	};

	Vector2f getPos() { return fly_s.getPosition(); };
	FloatRect getRect() { return fly_s.getGlobalBounds(); };
	Fly::State getState() { return state; };

	void setPos(Vector2f newPos) { fly_s.setPosition(newPos); };
	void setStateGrabbed() { state = GRABBED; };
	void setCurveParam(float xParam1, float xParam2, float yParam1, float yParam2)
	{
		this->xParam1 = xParam1;
		this->xParam2 = xParam2;
		this->yParam1 = yParam1;
		this->yParam2 = yParam2;
	}

};
