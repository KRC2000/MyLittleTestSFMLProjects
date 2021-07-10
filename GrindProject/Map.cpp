#include "Map.h"

Map::Map(String mapXmlPath, String name, b2World& world) : mapXmlPath(mapXmlPath), name(name), world(&world)
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
		while (column > tileset1Columns - 1)
		{
			column -= tileset1Columns;
			row++;
		}
		stamp.setTextureRect(IntRect(column * tileSize.x, row * tileSize.y, tileSize.x, tileSize.y));


		int xOffset = i;
		int yOffset = 0;
		while (xOffset > mapTileSize.x - 1)
		{
			xOffset -= mapTileSize.x;
			yOffset++;
		}
		stamp.setPosition({ (float)xOffset * tileSize.x, (float)yOffset * tileSize.y });
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

	//unique_ptr<tson::Map> map = t.parse("Map/tileMap1sss.json");

	//// extracting map tile size
	//mapTileSize = { map->getTileSize().x, map->getTileSize().y };

	//if (map->getStatus() == tson::ParseStatus::OK)
	//{
	//	tson::Layer* tileLayer1Ptr = map->getLayer("TileLayer1");

	//	if (tileLayer1Ptr->getType() == tson::LayerType::TileLayer)
	//	{
	//		if (!map->isInfinite())
	//		{
	//			std::map<std::tuple<int, int>, tson::Tile*> tileData = tileLayer1Ptr->getTileData();

	//			
	//			for (const auto& [id, tile] : tileData)
	//			{
	//				//Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
	//				//Would be unnecessary otherwise.
	//				int tileId;
	//				if (tile != nullptr)
	//					tileId = tile->getId(); //A bit verbose, as this is the same as id from the key, but you get the idea.
	//				cout << tileId;// << endl;
	//				mapIdDataVec.push_back(tileId);
	//			}
	//			//cout << mapTileSize.x << "   " << mapTileSize.y; 
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
	} while (iterator <= data_s.size() / sizeof(data_s[0]));


	// Extracting tile pixel size
	eMap->QueryIntAttribute("tilewidth", &tileSize.x);
	eMap->QueryIntAttribute("tileheight", &tileSize.y);

	// Extracting tile set xml file path
	tileSetXmlFileName = eTileset->Attribute("source");

	//Extracting objects
	tinyxml2::XMLElement* eObjgroup = eMap->FirstChildElement("objectgroup");
	tinyxml2::XMLElement* obj;
	if (eObjgroup != nullptr)
	{
		obj = eObjgroup->FirstChildElement("object");

		do
		{
			tinyxml2::XMLElement* ePolygon = obj->FirstChildElement("polygon");

			b2PolygonShape shape;
			b2BodyDef bdef;

			float x, y, width, height;
			obj->QueryFloatAttribute("x", &x);
			obj->QueryFloatAttribute("y", &y);
			if (ePolygon == nullptr)
			{

				obj->QueryFloatAttribute("width", &width);
				obj->QueryFloatAttribute("height", &height);

				shape.SetAsBox((width / 32.f) / 2.f, (height / 32.f) / 2.f);
				bdef.position.Set(x / 32 + (width / 32.f) / 2, y / 32 + (height / 32.f) / 2);
			}
			else
			{
				string data = ePolygon->Attribute("points");

				//vector<v2f> points;
				vector<b2Vec2> points;

				int iterator = 0;
				string s = "";
				do
				{

					if (data[iterator] == ' ' || iterator == data.size() / sizeof(data[0]))
					{
						string x_s = "", y_s = "";
						bool xd = false;
						for (int i = 0; i <= s.size() / sizeof(s[0]); i++)
						{
							if (s[i] == ',') { xd = true; continue; }
							if (xd == false) x_s += s[i];
							if (xd == true) y_s += s[i];
						}
						cout << x_s << "  " << y_s << endl;
						points.push_back({ (float)stoi(x_s) / 32, (float)stoi(y_s) / 32 });

						s = "";
					}
					else
					{
						s += data[iterator];
					}
					//cout << "boom";
					iterator++;
				} while (iterator <= data.size() / sizeof(data[0]));

				shape.Set(&points[0], points.size());
				bdef.position.Set(x / 32, y / 32);

			}

			//for (auto& point : points)


			b2Body* body = world->CreateBody(&bdef);
			body->CreateFixture(&shape, 1);
			colidersVec.push_back(body);

			obj = obj->NextSiblingElement("object");
		} while (obj != nullptr);
	}

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
