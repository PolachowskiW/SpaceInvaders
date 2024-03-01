//creating "Invader" class
#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Invader
{
private:
	//starting speed of every invader
	const float InvaderSpeed = 250;
	
	//health points assigned to each invader
	const float InvaderHealth = 1;
	
	//textures for each of invaders types
	Texture m_TextureA;
	Texture m_TextureB;
	Texture m_TextureC;

	//vector that stores position of the invader
	Vector2f m_Position;

	//instance of invader's sprite
	Sprite m_Sprite;

	//float that holds invader's current speed
	float m_Speed;

	//float that holds invader's current health
	float m_Health;

	//boolean that checks if invader still has not been shot
	bool m_Alive;

	//boolean that holds invader's movement condition
	bool bMove;

public:
	//constructor
	Invader();

	//function that updates invader after it's been shot by the player
	bool hit();

	//function that returns information about invader being alive or dead
	bool isAlive();

	//functions that updates invader every frame based on game's runtime and starting position of the invader
	void spawn(float startX, float startY, int type);

	//function that returns invader's bounds. Used for hit detection
	FloatRect getBounds();

	//function that return's invader's sprite so game can draw it in the arena
	Sprite getSprite();

	//function that returns invader's current position
	Vector2f getCenter();

	//function that moves invader to the left based on game's run time and movement condition
	void moveLeft(float elapsedTime, bool move);

	//function that moves invader to the right based on game's run time and movement condition
	void moveRight(float elapsedTime, bool move);

	//function that changes invader's vertical position
	void descend();

	//function that increases invader's speed after one of invaders has been shot down
	void SpeedBoost();
};
