//defining "InvaderBullet" functions
#include "InvaderBullet.h"

InvaderBullet::InvaderBullet()
{	
	//constructor holds size of invader's bullet
	m_BulletShape.setSize(sf::Vector2f(8, 18));
}

//shoot function that sets bullets state to true so it can start updating at randmly chosen invader's position
void InvaderBullet::shoot(float startX, float startY)
{	
	//changing bullet's state
	m_InFlight = true;
	
	//when bullet is being shot it changes it's color to white so it's visible in the arena
	m_BulletShape.setFillColor(sf::Color::White);
	
	//function sets starting position of bullet at randomly chosen invader's position
	m_Position.x = startX;
	m_Position.y = startY;

	//function sets position of bullet
	m_BulletShape.setPosition(m_Position);
}

//function that changes bullet's current state
void InvaderBullet::stop()
{
	m_InFlight = false;
}

//function that returns information about bullet's current state
bool InvaderBullet::isInFlight()
{
	return m_InFlight;
}

//function that returns bullet's global bounds for hit detection check
FloatRect InvaderBullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}

//function that returns bullet's shape so it can be drawn in the arena
RectangleShape InvaderBullet::getShape()
{
	return m_BulletShape;
}

//function that updates bullet each frame based on game's total run time
void InvaderBullet::update(float elapsedTime)
{
	//after bullet's state has been change to be in flight (has been shot)
	//it'll move only vertically towards player's position
	m_Position.y += m_BulletSpeed * elapsedTime;

	//function overwrites bullet's last position with position in the current frame
	m_BulletShape.setPosition(m_Position);

	//after bullet reaches bottom of the arena it's state changes so it won't be updated
	if (m_Position.y > 960)
	{
		m_InFlight = false;

		//bullet changes color to black so it looks like it disappeared
		m_BulletShape.setFillColor(sf::Color::Black);
	}
}