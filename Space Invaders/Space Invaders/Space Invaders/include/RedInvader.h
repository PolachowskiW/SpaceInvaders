//creating "RedInvader" class
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class RedInvader
{
private:
	//speed of red invader
	const float speed = 800;
	//health of red invader
	const float health = 1;

	//vector that holds current position of red invader
	Vector2f m_Position;

	//instance of red invader's sprite and texture
	Sprite m_Sprite;
	Texture m_Texture;

	//int that holds red invader's current health
	int m_Health;

	//boolean that holds current condition of red invader
	bool m_Alive;

	//float that holds current speed of red invader
	float m_Speed;

	//boolean that holds current movement condition of red invader
	bool bMove;

public:
	//constructor
	RedInvader();

	//function that will initialize red invader in the game loop
	void spawn();

	//function that will check if red invader has been shot by player
	bool hit();

	//function that will return information if red invader is alive after performing hit detection check
	bool isAlive();

	//function that resets red invader's state before start of each game
	void resetRedInvaderStats();

	//function that returns red invader's bounds for hit detection check
	FloatRect getBounds();

	//function that returns red invader's current position
	Vector2f getCenter();

	//function that returns red invader's sprite so the game can draw it in the arena
	Sprite getSprite();

	//function that will update red invader each frame
	void update(float elapsedTime);
};
