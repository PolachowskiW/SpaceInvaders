//defining "Bunker" class functions
#include "Bunker.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

Bunker::Bunker()
{	
	//constructor holds bunker's point of origin and it's health
	m_Health = BunkerHelath;
	m_Sprite.setOrigin(60, 30);
	
}

//function spawns bunkers in the arena based on position assigned to it by 'createBlockade' function
void Bunker::spawn(float startX, float startY)
{	
	//sprite uses texture loaded into Texture Holder's map
	m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Blockade1.png"));
	
	m_Position.x = startX;
	m_Position.y = startY;
	
	//function sets bunker's position
	m_Sprite.setPosition(m_Position);
	
}

//function returns last time bunker got hit
Time Bunker::getLastHitTime()
{
	return m_LastHit;
}

//functin returns bunker's health
int Bunker::getHealth()
{
	return m_Health;
}

//function updates bunker's current health after getting hit
bool Bunker::hit(Time timeHit)
{	
	//setting a time interval so bunker is not destroyed upon single hit (health is being updated each frame)
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 800)
	{
		//if bunker has been hit and time since last hit is longer, function decrements bunker's current health by 1
		//last time that bunker has been hit is overwritten so game can check if next incoming hit should decrement bunker's health
		m_LastHit = timeHit;
		m_Health --;
	}
	else
	{
		//if next incoming hit came too fast, game won't decrement bunker's health
		return false;
	}
	
	//if bunker's health level reaches 0 m_Alive returns 'false' and game stops updating bunker that's been hit
	if (m_Health == 0)
	{
		m_Alive = false;
		return true;
	}
}

//function that returns informaion wether bunker is alive or destroyed
bool Bunker::isAlive()
{
	return m_Alive;
}

// function returns bunker's global bounds for hit detection
FloatRect Bunker::getBounds()
{
	return m_Sprite.getGlobalBounds();
}

//function returns bunker's position
Vector2f Bunker::getCenter()
{
	return m_Position;
}

//function returns bunker's sprite so it can be drawn by game in the arena
Sprite Bunker::getSprite()
{
	return m_Sprite;
}

//function that updates each bunker each frame based on game's total run time
void Bunker::update(float elapsedTime)
{
	//bunker has different texture depending on it's current health points
	//all the textures are being stored in Texture holder so they only have to be loaded once
	if (m_Health == 3)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Blockade1.png"));
	}
	if (m_Health == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Blockade2.png"));
	}
	if (m_Health == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Blockade3.png"));
	}

	//function sets bunkers position
	m_Sprite.setPosition(m_Position);
}