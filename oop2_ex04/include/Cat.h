#pragma once
#include "MovingObject.h"
class Cat:public MovingObject
{
public:
	Cat();
	~Cat() {};

	void move(std::vector<std::vector<sf::CircleShape>>, sf::Time& deltaTime) ;
	void draw(sf::RenderWindow& window) const { window.draw(m_sprite); }
	void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }
	sf::Vector2f getPos() { return  m_sprite.getPosition(); };

private:
	
	sf::Sprite m_sprite;
	sf::Vector2f m_currDirection;

};
