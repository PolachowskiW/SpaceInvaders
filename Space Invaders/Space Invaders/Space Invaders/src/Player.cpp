//Defining functions of "Player" class
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "TextureHolder.h"

using namespace std;
using namespace sf;

Player::Player()
{	//constructor holds starting position of player sprite, as well as speed, health an texture 
	m_Speed = speed;
	m_Health = health;

	m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Ship.png"));
	
	//setting sprites origin point
	m_Sprite.setOrigin(30, 16);
	
	m_Position.x = 640;
	m_Position.y = 894;
}

//spawn function will set player's position to position defined in constructor
void Player::spawn()
{
	m_Position.x = 640;
	m_Position.y = 894;
}

//resetPlayerStats function will change players health back to 3 after starting new game
//function makes sure player's speed has not changed
void Player::resetPlayerStats()
{
	m_Speed = speed;
	m_Health = health;
}

//function returns last time player has been shot
Time Player::getLastHitTime()
{
	return m_LastHit;
}

//function will decrement player's health after they've been shot and last hit happened at least 1.2 seconds ago
bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 1200)
	{
		m_LastHit = timeHit;
		m_Health -= 1;
		return true;
	}
	//if player has been hit, but time from last hit is shorter than 1.2 seconds, player won't loose health point
	else
	{
		return false;
	}
}

//function sets player's bounds for hit detection
FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//functions returns player's current position
Vector2f Player::getCenter()
{
	return m_Position;
}

//function that returns player's sprite so the game can draw it on screen
Sprite Player::getSprite()
{
	return m_Sprite;
}

//function returns health so the game can determine in which state it should be
int Player::getHealth()
{
	return m_Health;
}

//function that sets condition for player's movement to the left
void Player::moveLeft()
{
	m_LeftPressed = true;
}

//function that sets condition for player's movement to the right
void Player::moveRight()
{
	m_RightPressed = true;
}

//function that sets condition for player's movement to the left
void Player::stopLeft()
{
	m_LeftPressed = false;
}

//function that sets condition for player's movement to the right
void Player::stopRight()
{
	m_RightPressed = false;
}

//function that updates player's position using game's run time and movement conditions defined above
void Player::update(float elapsedTime)
{
	//player will be moved to the right if conditions have been met
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	//player will be moved to the left if conditions have been met
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}
	//player's position is being updated each frame
	m_Sprite.setPosition(m_Position);

	//if player reache's screen's bounds it will be moved to defined position
	if (m_Position.x > 1250 )
	{
		m_Position.x = 1250;
	}
	if (m_Position.x < 30)
	{
		m_Position.x = 30;
	}

}