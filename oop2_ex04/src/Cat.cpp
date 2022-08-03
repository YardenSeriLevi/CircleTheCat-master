#include "Cat.h"


// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

//---------------------------------------------------
Cat::Cat()
{
	auto m_pTexture = FileManager::p2FileManager().getCatTexture();
	m_sprite.setTexture(*m_pTexture);
	m_sprite.scale(MOVING_OBJ_SCALE);
}


void Cat::move(std::vector<std::vector<sf::CircleShape>> grid, sf::Time& deltaTime)
{

	m_currDirection = sf::Vector2f(getNextMove(grid, m_sprite.getPosition()));
	if (m_currDirection != sf::Vector2f(-1, -1))
		m_sprite.setPosition(grid[m_currDirection.x][m_currDirection.y].getPosition());
}
