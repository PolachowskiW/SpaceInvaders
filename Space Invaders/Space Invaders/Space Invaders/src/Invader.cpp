//defining "Invader" class functions
#include "Invader.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>


using namespace std;

Invader::Invader()
{
	//constructor stores invader's point of origin, speed and health
	m_Speed = InvaderSpeed;
	m_Health = InvaderHealth;
	m_Sprite.setOrigin(24, 16);

}

//spawn function will draw invaders on assigned position with type assigned based on it's index number in "Horde" vertex array
void Invader::spawn(float startX, float startY, int type)
{	
	//each case loads different texture to distinguish invader types (different types give different amount of points to player)
	switch (type)
	{
	case 0:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\InvaderA1.png"));
		break;

	case 1:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\InvaderB1.png"));
		break;

	case 2:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\InvaderC1.png"));
		break;
	}

	//position is being set by "Horde" class 'createHorde' function
	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(24, 16);

	//function sets position using coordinates set by 'createHorde' function in "Horde" class
	m_Sprite.setPosition(m_Position);
}

//hit function will decrement invader's health after it's been hit by player's bullet
bool Invader::hit()
{
	m_Health--;

	//if invader has been hit and it's health drops to 0, function returns information that invader is not alive so it won't be updated anymore
	if (m_Health == 0)
	{
		m_Alive = false;

		return true;
	}
	
	//if invader has not been shot in the current frame, function  returns information that invader is still alive
	return false;
}

//function that determines wether invader will be updated by the game or not
bool Invader::isAlive()
{
	return m_Alive;
}

//function that returns invader's bounds so game can check if invader has been hit
FloatRect Invader::getBounds()
{
	return m_Sprite.getGlobalBounds();
}

//function returns invader's position so game can update it with the next frame
Vector2f Invader::getCenter()
{
	return m_Position;
}

//function that returns invader's sprite so the game can draw it on the arena
Sprite Invader::getSprite()
{
	return m_Sprite;
}

//function that moves invader to the right based on game run time and if condition is being met
void Invader::moveRight(float elapsedTime, bool move)
{	
	if (move)
	{
		m_Position.x = m_Position.x + (m_Speed * elapsedTime);
		
		//if invader reaches edge of the screen movement condition changes so it start's moving in the opposite direction
		if (m_Position.x < 0)
		{
			move = false;
		}
	}
	//function updates invader's position based on game's gun time and invader's speed
	m_Sprite.setPosition(m_Position);
}
//function that moves invader to the left based on game run time and if condition is bei
void Invader::moveLeft(float elapsedTime, bool move)
{
	if (!move)
	{
		m_Position.x = m_Position.x - (m_Speed * elapsedTime);
		
		//if invader reaches edge of the screen movement condition changes so it start's moving in the opposite direction
		if (m_Position.x < 0)
		{
			move = true;
		}
	}
	//function updates invader's position based on game's gun time and invader's speed
	m_Sprite.setPosition(m_Position);
}

//function changes invader's vertical position. It's being called out every time any invader reaches either left or right side of the screen
void Invader::descend()
{
	m_Position.y = m_Position.y + 15;
	
	//function updates invader's y position to current coordinates
	m_Sprite.setPosition(m_Position);
}

//function changes overall speed of all invaders. This function is called out every time an invader is shot down
void Invader::SpeedBoost()
{
	//every time speed is incremented by 3 and is being overwritten
	m_Speed = m_Speed + 3;
}

