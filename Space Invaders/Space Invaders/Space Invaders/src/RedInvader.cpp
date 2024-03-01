//defining "RedInvader" class functions
#include "RedInvader.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>


using namespace std;

RedInvader::RedInvader()
{
	//constructor holds red invader's speed, health and texture
	m_Speed = speed;
	m_Health = health;

	m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\RedInvader.png"));

	//constructor sets origin point for red invader
	m_Sprite.setOrigin(24, 16);
}

//function that spawns red invader at set position in the arena
void RedInvader::spawn()
{
	m_Position.x = -24;
	m_Position.y = 32;
	
	m_Sprite.setOrigin(24, 16);

	//function sets red invader's position to coordinates set at function's beginning
	m_Sprite.setPosition(m_Position);
}

//function that decrements red invader's health and changes 'alive' condition
bool RedInvader::hit()
{
	//when red invader is being shot, function decrements it's health by 1 point
	m_Health--;

	if (m_Health == 0)
	{
		//if red invader's health reaches 0, function returns information that it's not alive anymore so game won't be updating 
		//red invader anymore
		m_Alive = false;

		return true;
	}

	//if red invader has not been shot, function returns information that red invader is still alive, so the game would still update it
	return false;
}

//function returns red invader's health back to 1 and it's state to alive
void RedInvader::resetRedInvaderStats()
{
	m_Speed = speed;
	m_Health = health;
	m_Alive = true;
}

//function returns information about red invader's condition
bool RedInvader::isAlive()
{
	return m_Alive;
}

//function that returns red invader's global bounds for hit detection
FloatRect RedInvader::getBounds()
{
	return m_Sprite.getGlobalBounds();
}

//function that returns red invader's current position
Vector2f RedInvader::getCenter()
{
	return m_Position;
}

//function that returns red invader's sprite so the game can draw it in the arena
Sprite RedInvader::getSprite()
{
	return m_Sprite;
}

//function that updates red invader's movement direction and position based on game's run time and red invader's speed every frame
void RedInvader::update(float elapsedTime)
{
	//red invader will be moving right if movement condition is set to true
	if (bMove)
	{	
		//game sets red invader's position based on total game run time
		m_Position.x = m_Position.x + (m_Speed * elapsedTime);

		if (m_Position.x > 1328)
		{	
			//if red invader reaches this position, movement condition will change, changing red invader's movement direction
			bMove = false;
		}
	}
	else
	{
		//red invader will be moving left if movement condition is set to false
		//game sets red invader's position based on total game run time
		m_Position.x = m_Position.x - (m_Speed * elapsedTime);

		if (m_Position.x < -48)
		{
			//if red invader reaches this position, movement condition will change, changing red invader's movement direction
			bMove = true;	
		}
	}

	//function overwrites red invader's position with current position.
	m_Sprite.setPosition(m_Position);
}