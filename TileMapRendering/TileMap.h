#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TileMap :
    public Drawable
{
    RectangleShape stamp;
    RenderTexture r_texture;

public:
    TileMap(Vector2i mapSize, int tileArr[][5]  )
    {

    };

    virtual void draw(RenderTarget& target, RenderStates states) const
    {

    };
};

