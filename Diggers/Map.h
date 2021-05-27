#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Cell.h"

using namespace sf;
using namespace std;

struct Map : public sf::Drawable
{
	enum class MapTexturesEnum
	{ GROUND, STONE, AMOUNT};

	
	vector<Cell> cells_vec;
	RenderTexture backGround_rt;
	Sprite background_s;

	virtual ~Map() {};
	Map(int mapWidth, int mapHeight, float cellSize, vector<Texture>& mapTextures)
	{
		backGround_rt.create(mapWidth * cellSize, mapHeight * cellSize);
		Sprite temp_s(mapTextures[(int)MapTexturesEnum::GROUND]);
		for (int i = 0; i < mapWidth; i++)
		{
			for (int k = 0; k < mapHeight; k++)
			{
				temp_s.setPosition({i * cellSize, k * cellSize});
				backGround_rt.draw(temp_s);
			}
		}
		background_s.setTexture(backGround_rt.getTexture());

		for (int i = 0; i < mapWidth; i++)
		{
			for (int k = 0; k < mapHeight; k++)
			{
				if (rand() % 100 < 30)
				{
					Cell cell;
					cell.shape.setSize({ cellSize, cellSize });
					cell.shape.setPosition(i * cellSize, k * cellSize);
					mapTextures[(int)MapTexturesEnum::STONE].setRepeated(true);
					cell.shape.setTexture(&mapTextures[(int)MapTexturesEnum::STONE]);
					cell.shape.setTextureRect({0, 0, (int)mapTextures[(int)MapTexturesEnum::STONE].getSize().y, (int)mapTextures[(int)MapTexturesEnum::STONE].getSize().y });
					cell.health = 3;
					cells_vec.push_back(cell);
				}
			}
		}
	};
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(background_s);
		for (auto& cell : cells_vec)
			target.draw(cell.shape);
	};

	void deleteCell(Cell* cell_ptr)
	{
		if (cell_ptr)
		{
			for (int i = 0; i < cells_vec.size(); i++)
			{
				if (cell_ptr == &cells_vec[i])
					cells_vec.erase(cells_vec.begin() + i);
			}
		}
	};
};

