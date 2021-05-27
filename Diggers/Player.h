#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Cell.h"

using namespace sf;
using namespace std;

struct Player : public Drawable
{
	enum class Direction
	{ UP, DOWN, LEFT, RIGHT};

	RectangleShape player_s;

	virtual ~Player() {};
	Player(Texture& playerTexture, float cellSize): cellSize(cellSize)
	{
		player_s.setSize({ cellSize, cellSize });
		player_s.setTexture(&playerTexture);
		player_s.setTextureRect({33*0, 33*0, 33, 33});
	};
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(player_s);
	};

	void go(Direction direction, vector<Cell>& cells_vec)
	{
		Vector2f beforePos = player_s.getPosition();
		switch (direction)
		{
		case Player::Direction::UP:
			player_s.move(0, -cellSize);
			break;
		case Player::Direction::DOWN:
			player_s.move(0, cellSize);
			break;
		case Player::Direction::LEFT:
			player_s.move(-cellSize, 0);
			break;
		case Player::Direction::RIGHT:
			player_s.move(cellSize, 0);
			break;
		}

		for (auto& cell : cells_vec)
		{
			if (cell.shape.getPosition() == player_s.getPosition())
			{
				player_s.setPosition(beforePos);
			}
		}
	}
	// returns cell address if clicked cell is <= 0 hp (if any clicked)
	Cell* dig(Vector2f mousePos, vector<Cell>& cells_vec)
	{
		for (auto& cell : cells_vec)
		{
			if (cell.shape.getGlobalBounds().contains(mousePos))
			{
				if (cell.shape.getPosition().x == player_s.getPosition().x
					&& abs(cell.shape.getPosition().y - player_s.getPosition().y) <= cellSize
					|| cell.shape.getPosition().y == player_s.getPosition().y
					&& abs(cell.shape.getPosition().x - player_s.getPosition().x) <= cellSize)
				{
					cell.health--;
					cell.nextFrame();
					if (cell.health <= 0) return &cell;
				}
			}
		}
		return nullptr;
	};
private:
	float cellSize;
};

