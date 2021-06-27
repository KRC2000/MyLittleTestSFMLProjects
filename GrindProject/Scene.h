#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Scene: public Drawable
{
protected:
	String name;
	RenderWindow* window;
public:
	Scene(String name, RenderWindow& window):name(name), window(&window) {};
	virtual ~Scene() {};

	// gTime - global time, dTime - delta time
	virtual String update(Time gTime, Time dTime) = 0;
	virtual void processInputEvents(Event& event) = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

	String getName() { return name; };
};

