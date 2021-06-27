#include "Map.h"

Map::Map()
{
	extractTileMapIdData("Map/tileMap1.tmx", mapTileSize.x, mapTileSize.y);
}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	
}

/////////////////////////////////////////////
///////////// Private methods////////////////

void Map::extractTileMapIdData(String mapXmlPath, int& mapWidth, int& mapHeight)
{
	tinyxml2::XMLDocument mapXml;

	tinyxml2::XMLError eResult = mapXml.LoadFile(mapXmlPath.toAnsiString().c_str());
	if (eResult != tinyxml2::XML_SUCCESS) std::cout << "File loading failed!\n";

	tinyxml2::XMLElement* eMap = mapXml.FirstChildElement("map");
	tinyxml2::XMLElement* eLayer = eMap->FirstChildElement("layer");
	tinyxml2::XMLElement* eData = eLayer->FirstChildElement("data");
	tinyxml2::XMLElement* eChunk = eData->FirstChildElement("chunk");

	eChunk->QueryIntAttribute("width", &mapWidth);
	eChunk->QueryIntAttribute("height", &mapHeight);

	std::string data_s = eChunk->GetText();

	for (int i = 0; i < data_s.length(); i++)
	{
		if (data_s[i] != ',' && data_s[i] != '\n' && data_s[i] != '\0')
			mapIdDataVec.push_back(data_s[i] - 48);
	}

	for (int i = 0; i < mapIdDataVec.size(); i++)
	{
		if (i % mapWidth == 0) std::cout << std::endl;
		std::cout << mapIdDataVec[i];
	}

}
