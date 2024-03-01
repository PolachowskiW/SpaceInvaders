//defining "Bullet" class functions
#include "Bullet.h"

Bullet::Bullet()
{
	//constructor holds size, color and starting position of the rectangle shape that is player's bullet
	m_BulletShape.setSize(sf::Vector2f(6, 16));
	m_BulletShape.setFillColor(sf::Color::Green);
	m_BulletShape.setPosition(640, 976);
}

//function that changes bullet's state and set's it's position to player's current position so it's updated starting from player's position
void Bullet::shoot(float startX, float startY)
{
	//changing bullet's state so it's update can commence
	m_InFlight = true;
	m_BulletShape.setFillColor(sf::Color::Green);
	m_Position.x = startX;
	m_Position.y = startY;

	//function set's bullet's position to player's current position
	m_BulletShape.setPosition(m_Position);
}

//function that changes bullet's state so it stops getting updates
void Bullet::stop()
{
	m_InFlight = false;
}

//function that return's bullet's current state
bool Bullet::isInFlight()
{
	return m_InFlight;
}

//function that returns bullet's global boundfs for hit detection check
FloatRect Bullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}

//function that returns bullet's shape so it can be drawn in the arena
RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}

//function that updates bullet each frame based on game's total run time
void Bullet::update(float elapsedTime)
{
	//after being shot, bullet moves only vertically towards top of the screen
	m_Position.y -= m_BulletSpeed * elapsedTime;

	//function overwrites bullet's position with position in current frame
	m_BulletShape.setPosition(m_Position);

	if ( m_Position.y < 0)
	{	
		//if bullet reaches screen's top bound it's no longer being updated
		m_InFlight = false;
		
		//bullet's color is changed to black so it would look like it disappeared
		m_BulletShape.setFillColor(sf::Color::Black);
	}
}