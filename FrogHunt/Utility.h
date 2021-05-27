#pragma once
#include <iostream>
#include <vector>

namespace Utility
{
	const double PI = 3.141592;

	float radToDeg(float rad) // Tested
	{
		return rad * 180 / PI;
	}

	float degToRad(float deg) // Tested
	{
		return PI / 180 * deg;
	}

	float getVectorLenght(float xComp, float yComp)  // Tested
	{
		return abs(sqrt(xComp * xComp + yComp * yComp));
	};

	void normiliseVec(float& xComp, float& yComp) // Tested
	{
		float lenght = getVectorLenght(xComp, yComp);
		xComp = xComp / lenght;
		yComp = yComp / lenght;
	};

	// Get angle between two normalized vectors
	float getAngleBetweenNormVecs(float x1Comp, float y1Comp, float x2Comp, float y2Comp)
	{
		return acos(x1Comp * x2Comp + y1Comp * y2Comp);
	};

	// Get angle between vector and OX axis (1; 0)
	float getAngleNormVec(float xComp, float yComp) // Tested
	{
		return radToDeg((double)acos(xComp));
	};

	void rotateVec(float& xComp, float& yComp, float angle) // Tested
	{
		float radAngle = degToRad(angle);
		float rotatedXComp = xComp * cos(radAngle) - yComp * sin(radAngle);
		float rotatedYComp = xComp * sin(radAngle) - yComp * cos(radAngle);
		xComp = rotatedXComp;
		yComp = rotatedYComp;
	};

	float getRandFloat(int min, int max) // Tested
	{
		return (float)min + rand() % ((max - min) * 1000) / 1000.f;
	};

	int getRandInt(int min, int max)
	{
		return min + rand() % (max - min);
	};

	template <class myType>
	void fillVector(std::vector<myType> &vec, int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			vec.push_back(myType());
		}
	}

	template <class myType>
	void fillVector(std::vector<myType>& vec, int amount, myType refObject)
	{
		for (int i = 0; i < amount; i++)
		{
			vec.push_back(refObject);
		}
	}


};

