//creating "Bullet" class
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:

	//vector that holds bullet's position
	Vector2f m_Position;
	
	//inctance of a bullet
	RectangleShape m_BulletShape;

	//boolean that holds information about bullet's state
	bool m_InFlight = false;

	//float that holds bullet's speed
	float m_BulletSpeed = 850;


public:
	//constructor
	Bullet();

	//function that stops bullet at it's current position after hitting an invader
	void stop();

	//function that returns information about bullets state
	bool isInFlight();

	//function that shoots (starts updating) bullet from player's current location
	void shoot(float startX, float StartY);

	//function that returns bullet's bounds for hit detection check
	FloatRect getPosition();

	//function that returns rectangular shape of bullet
	RectangleShape getShape();

	//function that updates bullet each frame after player pressed spacebar and game called 'shoot' function 
	void update(float elapsedTime);

};
