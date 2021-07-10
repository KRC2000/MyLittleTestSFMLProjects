#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

using v2i = Vector2i;
using v2f = Vector2f;

class Camera: public sf::View
{
public:
	enum CamerMode { FREE_CAM, FOLLOW_CAM};
private:

	CamerMode camMode = FOLLOW_CAM;

	RenderTarget* target;
	bool mouseGrabbed = false;

	v2i mGrabPos{ 0, 0 };
	v2f viewInitPos{};

public:
	Camera(RenderTarget& target):target(&target) {};
	virtual ~Camera() {};

	// v2f point - point to follow or to be locked to
	void update(v2f point)
	{
		if (camMode == FOLLOW_CAM)
			setCenter(point);

		if (mouseGrabbed)
		{
			RenderWindow* window = dynamic_cast<RenderWindow*>(target);
			if (window)
			{
				v2i currentMpos = Mouse::getPosition(*window);
				setCenter(viewInitPos - (Vector2f)(currentMpos - mGrabPos));
			}
		}
	};

	void processInputEvents(Event& event)
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Middle)
			{
				if (camMode == FREE_CAM)
				{
					RenderWindow* window = dynamic_cast<RenderWindow*>(target);
					if (window)
					{
						mouseGrabbed = true;

						mGrabPos = Mouse::getPosition(*window);
						viewInitPos = getCenter();
					}
				}
			}
		}
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Middle)
			{
				if (camMode == FREE_CAM)
				{
					if (mouseGrabbed)
						mouseGrabbed = false;
				}
			}
		}
		if (event.type == Event::MouseWheelMoved)
		{
			if (camMode == FREE_CAM)
				zoom(1.f + -event.mouseWheel.delta/10.f);
		}

	};

	void setMode(Camera::CamerMode newMode)
	{
		camMode = newMode;
	};

};

