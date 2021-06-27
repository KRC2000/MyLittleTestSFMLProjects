#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
//#include <SFML/Network.hpp>
//#include <TGUI/TGUI.hpp>
//#include <vector>

//#include <box2d.h>

//#include "tinyxml2.h"

//b2Vec2 g;

//using namespace sf;
//using namespace std;
//using namespace tinyxml2;

//using v2f = Vector2f;

//const v2f SCR_SIZE = { 800, 600 };

int main()
{
	Game game;
	game.process();
	//RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	//XMLDocument xmlDoc;
	//XMLError eResult = xmlDoc.LoadFile("Map/tileMap1.tmx");
	//if (eResult == XML_SUCCESS) cout << "File loaded" << endl;

	//XMLElement* pRoot = xmlDoc.FirstChildElement("map");

	//int tileWidth, tileHeight;
	//pRoot->QueryIntAttribute("tilewidth", &tileWidth);
	//pRoot->QueryIntAttribute("tileheight", &tileHeight);
	//cout << "Tile width: " << tileWidth << "; Tile height: " << tileHeight << endl;

	//XMLElement* layer = pRoot->FirstChildElement("layer");
	//XMLElement* data = layer->FirstChildElement("data");
	//XMLElement* chunk = data->FirstChildElement("chunk");

	//int mapTileWidth, mapTileHeight;
	//chunk->QueryIntAttribute("width", &mapTileWidth);
	//chunk->QueryIntAttribute("height", &mapTileHeight);
	//cout << "Map rows: " << mapTileHeight << "; Map columns: " << mapTileWidth << endl;


	//string s = chunk->GetText();
	//vector<int> tileMapDat;
	//for (int i = 0; i < s.length(); i++)
	//{
	//	if (s[i] != ',' && s[i] != '\n' && s[i] != '\0')
	//		tileMapDat.push_back(s[i] - 48);
	//}
	//
	//for (int i = 0; i < tileMapDat.size(); i++)
	//{
	//	cout << tileMapDat[i];
	//	if (i % mapTileWidth == 0) cout << endl;
	//}

	//


	////XMLElement* element = pRoot->FirstChildElement("layer");
	//int id, width;
	////id = element->QueryIntText(&id);
	////width = element->QueryIntAttribute("width", &width);
	////cout << id << " " << width;



	//b2Vec2 gravity(0.0f, -10.0f);

	//b2World world(gravity);

	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);

	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);

	//groundBody->CreateFixture(&groundBox, 0.0f);

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);



	//tgui::GuiSFML gui{ window };

	//tgui::Button::Ptr button = tgui::Button::create();
	//auto editBox = tgui::EditBox::create();

	//tgui::Button::Ptr play_bPtr = tgui::Button::create("button_play");			gui.add(play_bPtr);
	//tgui::Button::Ptr exit_bPtr = tgui::Button::create("button_exit");			gui.add(exit_bPtr);
	//
	//
	//play_bPtr->setPosition({ "10%", 10 });
	//exit_bPtr->setPosition({ 10, 50 });
	//play_bPtr->setSize({ 150, 30 });
	//exit_bPtr->setSize({ 150, 30 });

	//Clock deltaTimer;

	//while (window.isOpen())
	//{
	//	v2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	//	float deltaTime = deltaTimer.restart().asSeconds();

	//	Event event;
	//	while (window.pollEvent(event))
	//	{
	//		gui.handleEvent(event);
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//		if (event.type == Event::KeyPressed)
	//		{
	//		}
	//	}


	//	window.clear();

	//	gui.draw();

	//	window.display();
	//}

	return 0;
};
