//defining "lives" class
#include "lives.h"
#include "TextureHolder.h"

Lives::Lives()
{
	//constructor holds lives origin point
	m_Sprite.setOrigin(30, 16);
}

//function that spawns lives using position assigned by "displayLives" function
void Lives::spawn(float startX, float startY)
{	
	//function assigns lives sprites textures using ship texture stored in texture holder map
	m_Sprite = Sprite(TextureHolder::GetTexture("assets\\images\\Ship.png"));

	//position of each life assigned by "displayLives" function
	m_Position.x = startX;
	m_Position.y = startY;

	//function sets position of each life
	m_Sprite.setPosition(m_Position);
}

//function that returns lives sprites so that they can be drawn in the arena
Sprite Lives::getSprite()
{
	return m_Sprite;
}