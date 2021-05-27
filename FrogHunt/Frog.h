#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Utility.h"

using namespace sf;
using namespace globVar;


class Frog : public Drawable
{
public:
	enum State { IDLE, FIRED, RETRIEVE };
private:
	Sprite frog_s, tongueBody_s, tongueHead_s;

	Vector2f dirVec{ 1,0 };
	float dirVec_angle = 0;
	Vector2f tongueStartPos{ 0, 0 };
	Vector2f defaultLocalTongueStartPos;
	Vector2f defaultFrog_sScale = { 0.7, 0.7 };
	float tongueLenght = 0;
	float tongueStrikeSpeed = 300;
	float tongueRetrieveSpeed = 900;

	bool eatAnimPlay = false;
	float eatAnimTimeStamp = 0;

	State state = IDLE;
public:

	Frog(std::vector<Texture>& t_vec)
	{
		frog_s.setTexture(t_vec[0]);
		tongueBody_s.setTexture(t_vec[1]);
		tongueHead_s.setTexture(t_vec[1]);

		frog_s.setOrigin(frog_s.getGlobalBounds().width / 2, frog_s.getGlobalBounds().height / 2);
		tongueBody_s.setTextureRect(IntRect(0, 0, 20, 5));
		tongueBody_s.setOrigin(0, tongueBody_s.getGlobalBounds().height / 2);
		tongueHead_s.setTextureRect(IntRect(0, 9, 8, 9));
		tongueHead_s.setOrigin(0, tongueHead_s.getGlobalBounds().height / 2);
		frog_s.setPosition(SCR_SIZE.x / 2, SCR_SIZE.y / 2);
		frog_s.setScale(defaultFrog_sScale);

		defaultLocalTongueStartPos = { frog_s.getGlobalBounds().width / 2 - 5, 0 };
	};

	void update(Vector2f mousePos, float deltaTime, float globalTime)
	{
		tongueStartPos = defaultLocalTongueStartPos;

		if (state == FIRED) tongueLenght += deltaTime * tongueStrikeSpeed;
		if (state == RETRIEVE) tongueLenght -= deltaTime * tongueRetrieveSpeed;
		if (tongueLenght < 0 && state == RETRIEVE)
		{
			tongueLenght = 0;
			state = IDLE;
		}


		if (state == IDLE)
		{
			dirVec = mousePos - frog_s.getPosition();
			Utility::normiliseVec(dirVec.x, dirVec.y);
			dirVec_angle = Utility::getAngleNormVec(dirVec.x, dirVec.y);
		}


		tongueBody_s.setTextureRect(IntRect(0, 0, tongueLenght, 5));





		if (dirVec.y > 0)
		{
			if (state == IDLE)
			{
				frog_s.setRotation(dirVec_angle);
				tongueBody_s.setRotation(dirVec_angle);
				tongueHead_s.setRotation(dirVec_angle);

			}
			Utility::rotateVec(tongueStartPos.x, tongueStartPos.y, dirVec_angle);
		}
		else
		{
			if (state == IDLE)
			{
				frog_s.setRotation(-dirVec_angle);
				tongueBody_s.setRotation(-dirVec_angle);
				tongueHead_s.setRotation(-dirVec_angle);

			}
			Utility::rotateVec(tongueStartPos.x, tongueStartPos.y, -dirVec_angle);
		}

		//std::cout << tongueStartPos.x << " : " << tongueStartPos.y << std::endl;



		if (!IntRect(0, 0, SCR_SIZE.x, SCR_SIZE.y).contains((Vector2i)tongueHead_s.getPosition()))
		{
			state = RETRIEVE;
		}

		if (state == IDLE)
		{
			tongueHead_s.setPosition(frog_s.getPosition() + tongueStartPos + dirVec * tongueLenght);
			tongueBody_s.setPosition(frog_s.getPosition() + tongueStartPos);

		}
		tongueHead_s.setPosition(frog_s.getPosition() + tongueStartPos + dirVec * tongueLenght);


		animUpdate(globalTime);

	};

	void fire()
	{
		if (state == IDLE) state = FIRED;
		else if (state == FIRED) state = RETRIEVE;
	};

	void playEatAnim(float globalTime)
	{
		eatAnimPlay = true;
		eatAnimTimeStamp = globalTime;
	}

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		if (state != IDLE) target.draw(tongueHead_s);
		target.draw(frog_s);
		if (state != IDLE) target.draw(tongueBody_s);
	};

	FloatRect getTongueHeadRect() { return tongueHead_s.getGlobalBounds(); };
	Vector2f getTongueHeadPos() { return tongueHead_s.getPosition(); };
	Frog::State getState() { return state; };

	void setStateRetrieve() { state = RETRIEVE; };

private:
	void animUpdate(float globalTime)
	{
		if (eatAnimPlay)
		{
			float eatAnimTime = 0.5;
			float elapsed = globalTime - eatAnimTimeStamp;
			if (elapsed > eatAnimTime / 4) frog_s.setScale(defaultFrog_sScale.x + 0.1, defaultFrog_sScale.y + 0.1);
			if (elapsed > eatAnimTime)
			{
				frog_s.setScale(defaultFrog_sScale);
				eatAnimPlay = false;
			}
		}
	}

};

