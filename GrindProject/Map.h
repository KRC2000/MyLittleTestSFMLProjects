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
	RenderTexture rt;
	Sprite rtHolder;

	std::vector<int> mapIdDataVec;
	v2i mapTileSize{ 0, 0 };

public:
	Map();
	virtual ~Map() {};

	virtual void draw(RenderTarget& target, RenderStates states) const;

private:
	void extractTileMapIdData(String mapXmlPath, int &mapWidth, int &mapHeight);
};

