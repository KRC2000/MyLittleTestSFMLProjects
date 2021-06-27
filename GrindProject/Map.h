#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <box2d.h>
#include "tinyxml2.h"
#include "tileson.hpp"

using namespace std;
using namespace sf;

using v2f = Vector2f;
using v2i = Vector2i;

class Map : public Drawable
{
	Texture tileset1_t;
	RenderTexture rt;
	Sprite rtHolder;

	String filetreePrefix = "Map/";
	String name = "";
	String mapXmlPath = "";
	String mapJsonPath = "Map/tileMap1sss.json";
	String tileSetXmlFileName = "";
	String tileSetTextureFileName = "";
	int tileset1TileCount = 0;
	int tileset1Columns = 0;

	b2World* world;
	//std::vector<IntRect> colidersRectVec;
	std::vector<b2Body*> colidersVec;
	std::vector<int> mapIdDataVec;
	v2i mapTileSize{ 0, 0 };
	v2i tileSize{ 0, 0 };

public:
	Map(String mapXmlFileName, String name, b2World& world);
	virtual ~Map() {};

	// Redraws tilemap to render texture
	void redraw();

	// Draws render texture to the target
	virtual void draw(RenderTarget& target, RenderStates states) const;

private:
	void extractTileMapData();
	void extractTilesetData(String tilesetXmlPath);
};

