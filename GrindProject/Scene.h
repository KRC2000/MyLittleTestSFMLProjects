#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Scene: public Drawable
{
protected:
	String name;
public:
	Scene(String name):name(name) {};
	virtual ~Scene() {};

	// gTime - global time, dTime - delta time
	virtual String update(RenderTarget& target, Event& event, Time gTime, Time dTime) = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

	String getName() { return name; };
};

