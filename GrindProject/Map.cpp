#include "Map.h"

Map::Map(String mapXmlPath, String name, b2World& world): mapXmlPath(mapXmlPath), name(name), world(&world)
{
	//extractTileMapIdData("Map/tileMap1.tmx");
	extractTileMapData();
	extractTilesetData(filetreePrefix + tileSetXmlFileName);

	if (!rt.create(tileSize.x * mapTileSize.x, tileSize.y * mapTileSize.y))
		cout << "Failed to create map render texture\n";

	rtHolder.setTexture(rt.getTexture());

	tileset1_t.loadFromFile(filetreePrefix + tileSetTextureFileName);
	redraw();
}

void Map::redraw()
{
	rt.clear(Color::Cyan);
	//cout << tileset1Columns;
	Sprite stamp(tileset1_t);
	for (int i = 0; i < mapIdDataVec.size(); i++)
	{
		int tileId = mapIdDataVec[i];
		if (tileId != 0) tileId--;
		int row = 0;
		int column = tileId;
		while (column > tileset1Columns-1)
		{
			column -= tileset1Columns;
			row++;
		}
		stamp.setTextureRect(IntRect(column * tileSize.x, row * tileSize.y, tileSize.x, tileSize.y));


		int xOffset = i;
		int yOffset = 0;
		while (xOffset > mapTileSize.x-1)
		{
			xOffset -= mapTileSize.x;
			yOffset++;
		}
		stamp.setPosition({(float)xOffset * tileSize.x, (float)yOffset * tileSize.y});
		//cout << xOffset << "     " << yOffset << endl;


		rt.draw(stamp);

	}

	rt.display();
}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(rtHolder);
}

/////////////////////////////////////////////
///////////// Private methods////////////////

void Map::extractTileMapData()
{
	//tson::Tileson t;

	////unique_ptr<tson::Map> map = t.parse(mapJsonPath.toAnsiString());

	//
	////const std::filesystem::path path = "Map/tileMap1sss.json";
	////fs::path path = "./Map/tileMap1sss.json";


	//unique_ptr<tson::Map> map = t.parse("Map/tileMap1sss.json");

	//if (map->getStatus() == tson::ParseStatus::OK)
	//{
	//	tson::Layer* tileLayer1Ptr = map->getLayer("TileLayer1");

	//	if (tileLayer1Ptr->getType() == tson::LayerType::TileLayer)
	//	{
	//		if (!map->isInfinite())
	//		{
	//			std::map<std::tuple<int, int>, tson::Tile*> tileData = tileLayer1Ptr->getTileData();

	//			tson::Vector2i mapTileSize = map->getTileSize();
	//			cout << mapTileSize.x << "   " << mapTileSize.y;
	//		}
	//	}
	//}















	tinyxml2::XMLDocument mapXml;

	tinyxml2::XMLError eResult = mapXml.LoadFile(mapXmlPath.toAnsiString().c_str());
	if (eResult != tinyxml2::XML_SUCCESS) std::cout << "Map xml file loading failed!\n";

	tinyxml2::XMLElement* eMap = mapXml.FirstChildElement("map");
	tinyxml2::XMLElement* eTileset = eMap->FirstChildElement("tileset");
	tinyxml2::XMLElement* eLayer = eMap->FirstChildElement("layer");
	tinyxml2::XMLElement* eData = eLayer->FirstChildElement("data");
	//tinyxml2::XMLElement* eChunk = eData->FirstChildElement("chunk");

	// Extracting map tile size
	eLayer->QueryIntAttribute("width", &mapTileSize.x);
	eLayer->QueryIntAttribute("height", &mapTileSize.y);

	// Extracting map id data
	std::string data_s = eData->GetText();

	int iterator = 0;
	String s = "";
	do
	{
		String t = data_s[iterator];
		if (t != ",") s += t;
		if (t == ",")
		{
			mapIdDataVec.push_back(stoi(s.toAnsiString()));
			//cout << s.toAnsiString() << endl;
			s = "";
		}
		iterator++;
		if (iterator == data_s.size() / sizeof(data_s[0])) mapIdDataVec.push_back(stoi(s.toAnsiString()));
	} while (iterator <= data_s.size()/sizeof(data_s[0]));


	// Extracting tile pixel size
	eMap->QueryIntAttribute("tilewidth", &tileSize.x);
	eMap->QueryIntAttribute("tileheight", &tileSize.y);

	// Extracting tile set xml file path
	tileSetXmlFileName = eTileset->Attribute("source");


	/*tinyxml2::XMLElement* object, *objectNext;
	object = eObjgroup->FirstChildElement("object");
	objectNext = object->NextSiblingElement("object");
	int id = 0;
	object->QueryIntAttribute("id", &id);
	cout << id;
	objectNext->QueryIntAttribute("id", &id);
	cout << id;*/
	

	/*tinyxml2::XMLElement* object;
	object = dynamic_cast<tinyxml2::XMLElement*>(eObjgroup->NextSibling());
	int id = 0;
	object->QueryIntAttribute("id", &id);
	cout << id;*/

	//Extracting objects
	tinyxml2::XMLElement* eObjgroup = eMap->FirstChildElement("objectgroup");
	tinyxml2::XMLElement* obj = eObjgroup->FirstChildElement("object");
	do
	{
		float x, y, width, height;
		obj->QueryFloatAttribute("x", &x);
		obj->QueryFloatAttribute("y", &y);
		obj->QueryFloatAttribute("width", &width);
		obj->QueryFloatAttribute("height", &height);

		b2PolygonShape shape;
		shape.SetAsBox((width/32.f) / 2.f, (height/32.f) / 2.f);
		b2BodyDef bdef;
		bdef.position.Set(x / 32 + (width/32.f) / 2, y / 32 + (height/32.f) / 2);
		b2Body* body = world->CreateBody(&bdef);
		body->CreateFixture(&shape, 1);
		colidersVec.push_back(body);

		obj = obj->NextSiblingElement("object");
	} while (obj != nullptr);
	
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

	// Extracting tileset column count
	tileset1Columns = std::stoi(eTileset->Attribute("columns"));
}
