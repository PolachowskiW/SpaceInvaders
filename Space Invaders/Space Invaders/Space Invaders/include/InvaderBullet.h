//creating "InvaderBullet" class
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class InvaderBullet
{
private:

	//vector that holds bullet's position
	Vector2f m_Position;

	//instance of bullet's shape
	RectangleShape m_BulletShape;

	//boolean stating bullet's state
	bool m_InFlight = false;

	//float that holds bullet's speed
	float m_BulletSpeed = 1000;


public:
	//constructor
	InvaderBullet();

	//function that changes bullet's state
	void stop();

	//function that returns bullet's current state
	bool isInFlight();

	//function that shoots(starts updating) the bullet based on random invader's position
	void shoot(float startX, float StartY);

	//function that returns bullet's global bounds for hit detection check
	FloatRect getPosition();

	//function that returns bullet's shape so it can be drawn in the arena
	RectangleShape getShape();

	//function that updates bullet each frame based on game's total run time
	void update(float elapsedTime);

};