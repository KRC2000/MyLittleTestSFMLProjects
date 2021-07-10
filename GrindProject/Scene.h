#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Scene: public Drawable
{
protected:
	String name;
	RenderWindow* window;
	const Time* gTime, const *dTime;
public:
	Scene(String name, RenderWindow& window,const Time& gTime, const Time& dTime)
		:name(name), window(&window), gTime(&gTime), dTime(&dTime) {};
	virtual ~Scene() {};

	// gTime - global time, dTime - delta time
	virtual String update() = 0;
	virtual void processInputEvents(Event& event) = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

	String getName() { return name; };
};

