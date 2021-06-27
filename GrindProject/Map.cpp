#include "Map.h"

Map::Map(String mapXmlPath, String name): mapXmlPath(mapXmlPath), name(name)
{
	//extractTileMapIdData("Map/tileMap1.tmx");
	extractTileMapData();
	extractTilesetData(filetreePrefix + tileSetXmlFileName);

	tileset1_t.loadFromFile(filetreePrefix + tileSetTextureFileName);
}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	
}

/////////////////////////////////////////////
///////////// Private methods////////////////

void Map::extractTileMapData()
{
	tinyxml2::XMLDocument mapXml;

	tinyxml2::XMLError eResult = mapXml.LoadFile(mapXmlPath.toAnsiString().c_str());
	if (eResult != tinyxml2::XML_SUCCESS) std::cout << "Map xml file loading failed!\n";

	tinyxml2::XMLElement* eMap = mapXml.FirstChildElement("map");
	tinyxml2::XMLElement* eTileset = eMap->FirstChildElement("tileset");
	tinyxml2::XMLElement* eLayer = eMap->FirstChildElement("layer");
	tinyxml2::XMLElement* eData = eLayer->FirstChildElement("data");
	tinyxml2::XMLElement* eChunk = eData->FirstChildElement("chunk");

	// Extracting map tile size
	eChunk->QueryIntAttribute("width", &mapTileSize.x);
	eChunk->QueryIntAttribute("height", &mapTileSize.y);

	// Extracting map id data
	std::string data_s = eChunk->GetText();

	for (int i = 0; i < data_s.length(); i++)
	{
		if (data_s[i] != ',' && data_s[i] != '\n' && data_s[i] != '\0')
			mapIdDataVec.push_back(data_s[i] - 48);
	}

	// Extracting tile pixel size
	eMap->QueryIntAttribute("tilewidth", &tileSize.x);
	eMap->QueryIntAttribute("tileheight", &tileSize.y);

	// Extracting tile set xml file path
	tileSetXmlFileName = eTileset->Attribute("source");

	
}

void Map::extractTilesetData(String tilesetXmlFilePath)
	{
	// Open xml file of tile set to get texture file name
	tinyxml2::XMLDocument tilesetXml;
	tinyxml2::XMLError eResult = tilesetXml.LoadFile(tilesetXmlFilePath.toAnsiString().c_str());
	if (eResult != tinyxml2::XML_SUCCESS) std::cout << "Tileset xml file loading failed!\n";

	tinyxml2::XMLElement* eTileset = tilesetXml.FirstChildElement("tileset");
	tinyxml2::XMLElement* eImage = eTileset->FirstChildElement("image");

	// Extracting tileset texture path
	tileSetTextureFileName = eImage->Attribute("source");

	// Extracting tileset tile count
	tileset1TileCount = std::stoi(eTileset->Attribute("tilecount"));
}
