//creating "Lives" class
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Lives
{
private:
	//vector that holds lives positions
	Vector2f m_Position;

	//instance of lives sprites
	Sprite m_Sprite;

public:
	//constructor
	Lives();

	//function that spawns lives in the arena
	void spawn(float startX, float startY);

	//function that returns lives sprites
	Sprite getSprite();
	
};
