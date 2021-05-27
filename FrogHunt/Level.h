#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Utility.h"
#include "Fly.h"

class Level
{
	std::vector<Fly>* flyVecPtr;
	Texture* fly_tPtr;
	bool initialised = false;

	unsigned int flies = 0;
	unsigned int maxFlies = 5;

public:
	Level(std::vector<Fly>& flyVec, Texture& fly_t)
	{
		flyVecPtr = &flyVec;
		fly_tPtr = &fly_t;
	};

	void update()
	{
		if (!initialised)
		{
			spawnMaxFlies();
			for (auto& fly : *flyVecPtr)
			{
				fly.init(*fly_tPtr);
				fly.setCurveParam(Utility::getRandFloat(1, 2), Utility::getRandInt(100, 400), Utility::getRandFloat(1, 2), Utility::getRandInt(100, 400));
			}
			initialised = true;

			//std::cout << Utility::getRandFloat(1, 3) << std::endl;
		}
		else
		{
			if (flyVecPtr->size() < maxFlies)
			{
				Fly f; f.init(*fly_tPtr);
				f.setCurveParam(Utility::getRandFloat(1, 2), Utility::getRandInt(100, 400), Utility::getRandFloat(1, 2), Utility::getRandInt(100, 400));
				flyVecPtr->push_back(f);
			}
		}

	};

	void spawnMaxFlies()
	{
		Utility::fillVector(*flyVecPtr, maxFlies);
	};
};