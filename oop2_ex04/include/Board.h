#pragma once
#include <memory>
#include<stdio.h>
#include <fstream>
#include <iostream>
#include "macros.h"
#include "cat.h"


using std::fstream;
class Board
{
public:
	Board();
	~Board() {};

	void draw(sf::RenderWindow& window)const;
	void mouseButtonReleased(sf::Event , sf::RenderWindow& , sf::Time );
	void mouseButtonMoved(sf::Event);
	void setClickCount(const int clicks) { m_clickCount = clicks; }
	int getClickCount()const { return m_clickCount; }
	void setWinLevel(const bool isWin) { m_winLevel = isWin; }
	bool getWinLevel() const { return m_winLevel; }
	void setLoseLevel(const bool isWin) { m_loseLevel = isWin; }
	bool getLoseLevel() const { return m_loseLevel; }
	void restartLevel();
	void startNewLevel();
	void undo();

private:
	void setBoard();
	void setGrid();
	void setLevel();
	void setCat();
	void doCatStuff(sf::Time& deltaTime);
	void SelectRandomColoredCircles();
	void UpdatePaintedCircles();
	void ColoringCirclesToBeginningColor();
	void UnColoringCurrentCircle(int, int);
	void coloringCurrentCircle(int, int);
	void drawGrid(sf::RenderWindow& window)const;
	void takeCatBackToPrevPos();

	sf::CircleShape m_movingCircle;
	int m_maxColoredCircles ;
	bool m_winLevel ;
	bool m_loseLevel ;
	bool m_restart ;
	int m_clickCount ;
	Cat m_cat;
	std::vector<std::vector<sf::CircleShape>> m_grid;
	std::vector<sf::Vector2f> m_randomColoredCircles;	
	std::vector<sf::Vector2f> m_clikedCircles;
	std::vector<sf::Vector2f> m_catWay;


};

