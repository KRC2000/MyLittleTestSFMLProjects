#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "tinyxml2.h"


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
	String tileSetXmlFileName = "";
	String tileSetTextureFileName = "";
	int tileset1TileCount = 0;
	int tileset1Columns = 0;

	std::vector<int> mapIdDataVec;
	v2i mapTileSize{ 0, 0 };
	v2i tileSize{ 0, 0 };

public:
	Map(String mapXmlFileName, String name);
	virtual ~Map() {};

	virtual void draw(RenderTarget& target, RenderStates states) const;

private:
	void extractTileMapData();
	void extractTilesetData(String tilesetXmlPath);
};

