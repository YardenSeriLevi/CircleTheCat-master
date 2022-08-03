#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "FileManager.h"
#include <deque>  
#include <queue> 
#include <limits.h>
#include <stdio.h>

using namespace std;
using std::vector;



class MovingObject
{
public:
	MovingObject() {};
	 virtual ~MovingObject() {};

	bool reachedTheExit() const { return m_reachedTheExit; }
	bool trapped() const { return m_trapped; }
	void resetReachedTheExit() { m_reachedTheExit = false; };
	void resetTrapped() { m_trapped = false; };

protected:
	sf::Vector2i getNextMove(std::vector<std::vector<sf::CircleShape>>, sf::Vector2f);

private:
	sf::Vector2i grillDirection(bool) const;
	bool isLineEven(int)const;
	bool winSituation(sf::Vector2i);
	bool isValid(int)const;
	sf::Vector2i moveObjectRandomly(std::vector<std::vector<sf::CircleShape>>, sf::Vector2i);
	sf::Vector2i fillVisitedAndFindSource(std::vector<std::vector<sf::CircleShape>>
		, bool[BOARD_LEN][BOARD_LEN], sf::Vector2f);
	void resetMatrix(std::vector<std::vector<sf::Vector2<int>>>&);
	sf::Vector2i calaulateFirstMove(std::vector<std::vector<sf::Vector2<int>>>, sf::Vector2i, sf::Vector2i);
	bool canMove(std::vector<std::vector<sf::CircleShape>>, sf::Vector2i);
	void checkDirection( sf::Vector2i, bool visited[BOARD_LEN][BOARD_LEN],
		std::queue<sf::Vector2i>& q,
		std::vector<std::vector<sf::Vector2i>>& discover, sf::Vector2i p);

	bool m_reachedTheExit = false;
	bool m_trapped = false;
};
