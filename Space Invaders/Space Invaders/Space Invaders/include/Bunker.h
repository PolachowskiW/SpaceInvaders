//creating "bunker" class
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bunker
{
private:
	//float that stores bunker's health points
	const float	BunkerHelath = 3;

	//vector that holds bunker's position
	Vector2f m_Position;

	//instance of bunker's sprite
	Sprite m_Sprite;

	//float that holds bunker's current health
	float m_Health;

	//bool that stores information about bunker being alive or not
	bool m_Alive;


public:
	//constructor
	Bunker();

	//function that returns last time bunker got hit
	Time getLastHitTime();

	//function that updates bunker's health after getting hit
	bool hit(Time timeHit);

	//function that returns information about bunker being alive or destroyed
	bool isAlive();

	//function that spawns bunkers using position set by  'buildBlockade' function in "Blockade" class
	void spawn(float startX, float startY);

	//timer that holds time since last time bunker's been hit
	Time m_LastHit;
	
	//function that returns bunker's global bounds for hit detection
	FloatRect getBounds();

	//function that returns bunker's sprite so it can be drawn in the arena
	Sprite getSprite();

	//function that returns bunker's position
	Vector2f getCenter();

	//function that updates bunker each frame based on game's total run time
	void update(float elapsedTime);
	
	//function that returns bunker's current health
	int getHealth();
};
