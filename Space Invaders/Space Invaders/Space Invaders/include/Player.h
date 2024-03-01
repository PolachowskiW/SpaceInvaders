//creating "Player" class
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player
{
private:
	//float values for player's health and speed
	//'speed' float is used by "Player" class move left/right functions to determine player's position
	//'health' float is used by "Player" class hit function that helps to determine in which state game should be depending on player's current health
	const float speed = 800;
	const float health = 3;

	//Vector that stores player's position after updating each frame
	Vector2f m_Position;

	//instance of sprite and texture used to draw player's character
	Sprite m_Sprite;
	Texture m_Texture;

	//booleans used to determine wether player is currently moving left or right
	bool m_LeftPressed;
	bool m_RightPressed;

	//int value that stores player's current health
	int m_Health;
	
	//timer that stores last time player has been hit
	//used by "Player" class hit function to reduce amount of hits player can receive in certain amount of time
	Time m_LastHit;
	
	//float that holds player's current speed
	float m_Speed;

public:
	//constructor
	Player();
	
	//function that will spawn player's sprite oinn the game arena
	void spawn();
	
	//function that will reset player's speed and health after losing a game
	void resetPlayerStats();
	
	//function that update's player's health after getting shot
	bool hit(Time timeHit);
	
	//function that will return last time player has been hit
	Time getLastHitTime();
	
	//function that will retern player's global bounds to detect if player has been shot
	FloatRect getPosition();
	
	//function that returns player's current position
	Vector2f getCenter();
	
	//function that returns player's sprite
	Sprite getSprite();
	
	//function that moves player's sprite to the left
	void moveLeft();
	
	//function that moves player's sprite to the right
	void moveRight();
	
	//function that stops player's sprite after left button movement has been released
	void stopLeft();
	
	//function that stops player's sprite after right button movement has been released
	void stopRight();

	//function that updates player's sprite every milisecond
	void update(float elapsedTime);

	//function that return's player's current healths
	int getHealth();
};
